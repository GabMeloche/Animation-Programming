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
		//Matrix4<float> newTrans = p_bone->GetParent()->GetWorldTransform() * p_bone->GetLocalTransform();
		Matrix4<float> worldTPos = p_bone->GetParent()->GetWorldTPose() * p_bone->GetLocalTPose();

		//TODO
		//p_bone->SetWorldTransform(newTrans);
		p_bone->SetWorldTPose(worldTPos);
	}
	else
	{
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

void Skeleton::Animate(const char* p_anim, int p_frame)
{
	float posX, posY, posZ, quatW, quatX, quatY, quatZ;

	float matrices[976];
	
	for (int i = 0; i < m_bones.size(); ++i)
	{
		GetAnimLocalBoneTransform(p_anim, i, p_frame, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		GPM::Matrix4<float> anim = GPM::Matrix4<float>::CreateTransformation(
			GPM::Vector3<float>{posX, posY, posZ}, 
			GPM::Quaternion{ quatX, quatY, quatZ, quatW },
			{1, 1, 1});

		
		m_bones[i].SetWorldTransform(m_bones[i].GetLocalTPose() * anim);

		if (m_bones[i].GetParent())
			m_bones[i].m_FinalMat = m_bones[i].GetParent()->m_FinalMat * m_bones[i].GetWorldTransform();
		else
			m_bones[i].m_FinalMat = m_bones[i].GetWorldTransform();
		
		Matrix4F patate = m_bones[i].m_FinalMat * GPM::Matrix4F::Inverse(m_bones[i].GetWorldTPose());
		
		int matrixIndex = 0;

		/*for (int j = i * 16; j < 16 + (i * 16); ++j)
		{
			matrices[j] = patate[matrixIndex];
			++matrixIndex;
		}*/
		for (int j = 0; j < 16; ++j)
		{
			matrices[(i * 16) + j] = patate[j];
		}
	}
	
	SetSkinningPose(matrices, m_bones.size());
}

