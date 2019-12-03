#include "Skeleton.h"
#include "Engine.h"
#include <stdio.h>

Skeleton::Skeleton()
{
	const int boneCount = GetSkeletonBoneCount();

	for (int i = 0; i < boneCount - 7; ++i)
	{
		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		GetSkeletonBoneLocalBindTransform(i, posX, posY, posZ, quatW, quatX, quatY, quatZ);

		printf("\nparent bone : %s\n", GetSkeletonBoneName(i));
		printf("Anim key count : %ld\n", 0);
		printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
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
		}
	}
	
	ComputeSkeleton();
	CalculateBoneInverses();
}

void Skeleton::DrawSkeleton()
{
	const float lineSizeMultiplier = 1.0f;
	
	for (auto& bone: m_bones)
	{
		GPM::Matrix4<float>& boneWorld = bone.GetWorldTransform();
		
		if (bone.GetParent() != nullptr)
		{
			GPM::Matrix4<float>& parentWorld = bone.GetParent()->GetWorldTransform();
			
			DrawLine(parentWorld[3] * lineSizeMultiplier, parentWorld[7] * lineSizeMultiplier, parentWorld[11] * lineSizeMultiplier,
				boneWorld[3] * lineSizeMultiplier, boneWorld[7] * lineSizeMultiplier, boneWorld[11] * lineSizeMultiplier, 0, 1, 1);
		}
	}
}

void Skeleton::ComputeSkeleton()
{
	ComputeBones(m_root);
}

void Skeleton::CalculateBoneInverses()
{
	for (auto& bone : m_bones)
		bone.CalculateInverted();
}

void Skeleton::ComputeBones(Bone* p_bone)
{
	if (p_bone == nullptr)
		return;

	if (p_bone->GetParent() != nullptr)
	{
		Matrix4<float> newTrans = p_bone->GetParent()->GetWorldTransform() * p_bone->GetLocalTransform();
		p_bone->SetWorldTransform(newTrans);
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

void Skeleton::Animate(const char* p_anim, int p_frame)
{
	float posX, posY, posZ, quatW, quatX, quatY, quatZ;
	
	for (int i = 0; i < m_bones.size(); ++i)
	{
		GetAnimLocalBoneTransform(p_anim, i, p_frame, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		GPM::Matrix4<float> anim = GPM::Matrix4<float>::CreateTransformation(
			GPM::Vector3<float>{posX, posY, posZ}, 
			GPM::Quaternion{ quatX, quatY, quatZ, quatW },
			{1, 1, 1});

		if (m_bones[i].GetParent())
			anim = m_bones[i].GetParent()->GetWorldTransform() * anim;

		/*std::cout << "anim transform: \n" << m_bones[i].GetName() << std::endl << anim << std::endl << std::endl;
		std::cout << "local transform: \n" << m_bones[i].GetLocalTransform() << std::endl;*/

		m_bones[i].SetWorldTransform(anim * m_bones[i].GetWorldTPose());
		Matrix4<float>& matrix = m_bones[i].GetWorldTransform();
		
		float* floats = new float[matrix[0], matrix[1], matrix[2], matrix[3],
			matrix[4], matrix[5], matrix[6], matrix[7],
			matrix[8], matrix[9], matrix[10], matrix[11],
			matrix[12], matrix[13], matrix[14], matrix[15]];
		
		SetSkinningPose(floats, i);
		
		delete[] floats;
	}
}

