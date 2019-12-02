#include "Skeleton.h"
#include "Engine.h"
#include <stdio.h>

Skeleton::Skeleton(const char* p_anim)
{
	const int boneCount = GetSkeletonBoneCount();

	for (int i = 0; i < boneCount - 7; ++i)
	{
		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		GetAnimLocalBoneTransform(p_anim, i, 0, posX, posY, posZ, quatW, quatX, quatY, quatZ);

		m_bones.emplace_back(GPM::Vector3<float>{posX, posY, posZ}, GPM::Quaternion{ quatX, quatY, quatZ, quatW });
		m_bones[i].SetName(GetSkeletonBoneName(i));

		printf("\nparent bone : %s\n", GetSkeletonBoneName(i));
		printf("Anim key count : %ld\n", 0);
		printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);
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
			m_bones[i].SetWorldPos(m_bones[i].GetLocalPos());
		}
	}
	UpdateSkeleton();
}

void Skeleton::DrawSkeleton()
{
	UpdateSkeleton();
	const float lineSizeMultiplier = 10.0f;

	for (int i = 0; i < m_bones.size(); ++i)
	{
		GPM::Vector3<float>& parent = m_bones[i].GetWorldPos();

		for (int j = 0; j < m_bones[i].GetChildren().size(); ++i)
		{
			GPM::Vector3<float>& child = m_bones[i].GetChildren()[j]->GetWorldPos();
			DrawLine(parent.x * lineSizeMultiplier, parent.y * lineSizeMultiplier, parent.z * lineSizeMultiplier,
				child.x * lineSizeMultiplier, child.y * lineSizeMultiplier, child.z * lineSizeMultiplier, 0, 1, 1);
		}
	}
}

void Skeleton::UpdateSkeleton()
{
	UpdateBones(m_root);
}

void Skeleton::UpdateBones(Bone* p_bone)
{
	if (p_bone == nullptr)
		return;

	if (p_bone->GetParent() != nullptr)
	{
		Vector3<float> newPos = p_bone->GetLocalPos() + p_bone->GetParent()->GetWorldPos();
		p_bone->SetWorldPos(newPos);
	}


	for (int i = 0; i < p_bone->GetChildren().size(); ++i)
	{
		UpdateBones(p_bone->GetChildren()[i]);
	}
}

void Skeleton::PrintSkeleton()
{
	std::cout << "\n\n----PRINT SKELETON----\n\n";

	for (auto& bone : m_bones)
	{
		std::cout << bone.GetName() << "\n  worldPos: " << bone.GetWorldPos() << "\n  localPos: " << bone.GetLocalPos() << "\n  worldRot: " << bone.GetRotation() << std::endl << "  children: \n\n";
		for (auto child : bone.GetChildren())
		{
			std::cout << "  - " << child->GetName() << "\n    worldPos: " << child->GetWorldPos() << "\n    localPos: " << child->GetLocalPos() << "\n    worldRot: " << child->GetRotation() << std::endl << std::endl;
		}
		std::cout << "\n\n";
	}

	std::cout << "\n\n----END PRINT SKELETON----\n\n";
}

