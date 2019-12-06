#include <Engine/Engine.h>
#include <Skeleton/Skeleton.h>

Skeleton::Skeleton()
{
	const int boneCount = GetSkeletonBoneCount();

	//Create Bones
	for (int i = 0; i < boneCount - 7; ++i)
	{
		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		GetSkeletonBoneLocalBindTransform(i, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		m_bones.emplace_back(GPM::Vector3<float>{posX, posY, posZ}, GPM::Quaternion{ quatX, quatY, quatZ, quatW });
		m_bones[i].SetName(GetSkeletonBoneName(i));
	}

	m_root = &m_bones[0];

	//Set parent-child links
	for (int i = 0; i < boneCount - 7; ++i)
	{
		const int parent = GetSkeletonBoneParentIndex(i);

		if (parent != -1)
		{
			m_bones[i].SetParent(&m_bones[parent]);
			m_bones[parent].EmplaceBackChildren(&m_bones[i]);
		}
		else
		{
			m_bones[i].SetWorldTransform(m_bones[i].GetLocalTransform());
			m_bones[i].SetWorldTPose(m_bones[i].GetLocalTransform());
		}
	}

	//Compute world transforms
	ComputeSkeleton();
}

void Skeleton::DrawSkeleton(const GPM::Vector3F& p_color)
{
	for (auto& bone: m_bones)
	{
		GPM::Matrix4<float>& boneWorld = bone.GetWorldTransform();
		
		if (bone.GetParent() != nullptr)
		{
			GPM::Matrix4<float>& parentWorld = bone.GetParent()->GetWorldTransform();
			
			DrawLine(parentWorld[3], parentWorld[7], parentWorld[11],
				boneWorld[3], boneWorld[7], boneWorld[11], 
				p_color.x, p_color.y, p_color.z);
		}

	}
}

void Skeleton::DrawTPose(const GPM::Vector3F& p_color)
{
	for (auto& bone : m_bones)
	{
		GPM::Matrix4<float>& boneWorld = bone.GetWorldTPose();

		if (bone.GetParent() != nullptr)
		{
			GPM::Matrix4<float>& parentWorld = bone.GetParent()->GetWorldTPose();

			DrawLine(parentWorld[3], parentWorld[7], parentWorld[11],
				boneWorld[3], boneWorld[7], boneWorld[11], 
				p_color.x, p_color.y, p_color.z);
		}

	}
}

void Skeleton::ComputeSkeleton()
{
	ComputeBones(m_root);
}

void Skeleton::ComputeBones(Bone* p_bone)
{
	if (p_bone == nullptr)
		return;

	if (p_bone->GetParent() != nullptr)
	{
		const Matrix4<float> worldTPos = p_bone->GetParent()->GetWorldTPose() * p_bone->GetLocalTPose();

		p_bone->SetWorldTransform(worldTPos);
		p_bone->SetWorldTPose(worldTPos);
	}
	else
	{
		p_bone->SetWorldTransform(p_bone->GetLocalTransform());
		p_bone->SetWorldTPose(p_bone->GetLocalTPose());
	}
	
	for (auto child: p_bone->GetChildren())
	{
		ComputeBones(child);
	}
}

void Skeleton::PrintSkeleton()
{
	std::cout << "\n\n----PRINT SKELETON----\n\n";

	for (auto& bone : m_bones)
	{
		std::cout << bone.GetName() << "\n  worldPos: \n" << bone.GetWorldTransform() << "\n  localPos: \n" << bone.GetLocalTransform() << "  children: \n\n";
		for (auto child : bone.GetChildren())
		{
			std::cout << "  - " << child->GetName() << "\n    worldPos: \n" << child->GetWorldTransform() << "\n    localPos: \n" << child->GetLocalTransform() << std::endl << std::endl;
		}
		std::cout << "\n\n";
	}

	std::cout << "\n\n----END PRINT SKELETON----\n\n";
}

void Skeleton::Animate(int p_animationIndex, float p_time, float p_animSpeed)
{
	const unsigned int keyFrames = m_animations[p_animationIndex].GetAnimSkeletons().size();
	const float animTime = p_time * p_animSpeed * 30; //animations are sampled at 30 frames / second
	const int timer = static_cast<int>(animTime);
	unsigned int currentFrame = static_cast<int>(animTime) % keyFrames;
	unsigned int nextFrame = currentFrame + 1;

	if (p_animSpeed < 0)
	{
		const unsigned int tmp = currentFrame;
		nextFrame = currentFrame;
		currentFrame = tmp;
	}
	
	if (nextFrame >= keyFrames)
	{
		nextFrame = 0;
	}
	
	float* matrices = new float[m_bones.size() * 16];
	
	for (size_t i = 0; i < m_bones.size(); ++i)
	{
		if (p_animationIndex >= 0)
		{
			Vector3F pos1 = m_animations[p_animationIndex].GetAnimSkeletons()[currentFrame].m_animBones[i].m_position;
			Vector3F pos2 = m_animations[p_animationIndex].GetAnimSkeletons()[nextFrame].m_animBones[i].m_position;

			Quaternion quat1 = m_animations[p_animationIndex].GetAnimSkeletons()[currentFrame].m_animBones[i].m_quaternion;
			Quaternion quat2 = m_animations[p_animationIndex].GetAnimSkeletons()[nextFrame].m_animBones[i].m_quaternion;

			Vector3F posFinal = GPM::Vector3F::Lerp(pos1, pos2,  animTime - static_cast<float>(timer));
			Quaternion quatFinal = GPM::Quaternion::SlerpShortestPath(quat1, quat2, animTime - static_cast<float>(timer));

			GPM::Matrix4F anim = GPM::Matrix4F::CreateTransformation(posFinal, quatFinal, { 1, 1, 1 });

			m_bones[i].SetWorldTransform(m_bones[i].GetLocalTPose() * anim);
		}
		else
			m_bones[i].SetWorldTransform(m_bones[i].GetLocalTPose());
		
		if (m_bones[i].GetParent())
			m_bones[i].GetWorldTransform() = m_bones[i].GetParent()->GetWorldTransform() * m_bones[i].GetWorldTransform();
		
		Matrix4F finalMatrix = m_bones[i].GetWorldTransform() * GPM::Matrix4F::Inverse(m_bones[i].GetWorldTPose());
		
		int matrixIndex = 0;

		for (size_t j = i * 16; j < 16 + (i * 16); ++j)
		{
			matrices[j] = finalMatrix[matrixIndex];
			++matrixIndex;
		}
	}
	
	SetSkinningPose(matrices, m_bones.size());
	delete[] matrices;
}

void Skeleton::AddAnimation(const char* p_anim, const char* p_name)
{
	m_animations.emplace_back(Animation{ p_anim, p_name });
}

