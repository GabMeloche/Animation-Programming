#include "Engine.h"
#include "Skeleton.h"

Skeleton::Skeleton()
{
	const int boneCount = GetSkeletonBoneCount();

	for (int i = 0; i < boneCount - 7; ++i)
	{
		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		GetSkeletonBoneLocalBindTransform(i, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		m_bones.emplace_back(GPM::Vector3<float>{posX, posY, posZ}, GPM::Quaternion{ quatX, quatY, quatZ, quatW });
		m_bones[i].SetName(GetSkeletonBoneName(i));

	}

	m_root = &m_bones[0];

	for (int i = 0; i < boneCount - 7; ++i)
	{
		int parent = GetSkeletonBoneParentIndex(i);

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
	
	ComputeSkeleton();
}

void Skeleton::DrawSkeleton(const GPM::Vector3F& p_color)
{
	const float lineSizeMultiplier = 1.0f;
	
	for (auto& bone: m_bones)
	{
		GPM::Matrix4<float>& boneWorld = bone.m_FinalMat;
		
		if (bone.GetParent() != nullptr)
		{
			GPM::Matrix4<float>& parentWorld = bone.GetParent()->m_FinalMat;
			
			DrawLine(parentWorld[3] * lineSizeMultiplier, parentWorld[7] * lineSizeMultiplier, parentWorld[11] * lineSizeMultiplier,
				boneWorld[3] * lineSizeMultiplier, boneWorld[7] * lineSizeMultiplier, boneWorld[11] * lineSizeMultiplier, p_color.x, p_color.y, p_color.z);
		}

	}
}

void Skeleton::DrawTPose(const GPM::Vector3F& p_color)
{
	const float lineSizeMultiplier = 1.0f;

	for (auto& bone : m_bones)
	{
		GPM::Matrix4<float>& boneWorld = bone.GetWorldTPose();

		if (bone.GetParent() != nullptr)
		{
			GPM::Matrix4<float>& parentWorld = bone.GetParent()->GetWorldTPose();

			DrawLine(parentWorld[3] * lineSizeMultiplier, parentWorld[7] * lineSizeMultiplier, parentWorld[11] * lineSizeMultiplier,
				boneWorld[3] * lineSizeMultiplier, boneWorld[7] * lineSizeMultiplier, boneWorld[11] * lineSizeMultiplier, p_color.x, p_color.y, p_color.z);
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
		//Matrix4<float> newTrans = p_bone->GetParent()->GetWorldTransform() * p_bone->GetLocalTransform();
		Matrix4<float> worldTPos = p_bone->GetParent()->GetWorldTPose() * p_bone->GetLocalTPose();

		//TODO
		p_bone->SetWorldTransform(worldTPos);
		p_bone->SetWorldTPose(worldTPos);
	}
	else
	{
		p_bone->SetWorldTransform(p_bone->GetLocalTransform());
		p_bone->SetWorldTPose(p_bone->GetLocalTPose());
	}
	
	for (int i = 0; i < p_bone->GetChildren().size(); ++i)
	{
		ComputeBones(p_bone->GetChildren()[i]);
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

void Skeleton::Animate(int p_animationIndex, int p_frame)
{
	float posX, posY, posZ, quatW, quatX, quatY, quatZ;

	float matrices[976];
	
	for (int i = 0; i < m_bones.size(); ++i)
	{
		m_bones[i].SetWorldTransform(m_animations[p_animationIndex].GetSkeletons()[p_frame].GetBones()[i].GetLocalTransform());

		if (m_bones[i].GetParent())
			m_bones[i].m_FinalMat = m_bones[i].GetParent()->m_FinalMat * m_bones[i].GetWorldTransform();
		else
			m_bones[i].m_FinalMat = m_bones[i].GetWorldTransform();
		
		Matrix4F patate = m_bones[i].m_FinalMat * GPM::Matrix4F::Inverse(m_bones[i].GetWorldTPose());
		
		int matrixIndex = 0;

		for (int j = i * 16; j < 16 + (i * 16); ++j)
		{
			matrices[j] = patate[matrixIndex];
			++matrixIndex;
		}
	}
	
	SetSkinningPose(matrices, m_bones.size());
}

void Skeleton::AddAnimation(const char* p_anim, const char* p_name)
{
	m_animations.emplace_back(Animation{ p_anim, p_name });
}

