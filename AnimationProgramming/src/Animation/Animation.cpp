#include <Engine/Engine.h>
#include <Animation/Animation.h>
#include <Skeleton/Skeleton.h>

Animation::Animation(const char* p_anim, const char* p_name): m_name { p_name }
{
	float posX, posY, posZ, quatW, quatX, quatY, quatZ;

	//Keyframe
	for (size_t k = 0; k < GetAnimKeyCount(p_anim); ++k)
	{
		m_animSkeletons.emplace_back(AnimSkeleton());

		//Bone
		for (size_t i = 0; i < GetSkeletonBoneCount() - 7; ++i)
		{
			m_animSkeletons[k].m_animBones.emplace_back(AnimBone());
			
			GetAnimLocalBoneTransform(p_anim, i, k, posX, posY, posZ, quatW, quatX, quatY, quatZ);

			m_animSkeletons[k].m_animBones[i].m_position = { posX, posY, posZ };
			m_animSkeletons[k].m_animBones[i].m_quaternion = { quatX, quatY, quatZ, quatW };
		}
	}
}
