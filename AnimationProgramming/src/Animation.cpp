#include "Engine.h"
#include <Animation.h>
#include <Skeleton.h>

Animation::Animation(const char* p_anim, const char* p_name): m_name { p_name }
{
	float posX, posY, posZ, quatW, quatX, quatY, quatZ;

	//Keyframe
	for (int k = 0; k < GetAnimKeyCount(p_anim); ++k)
	{
		m_skeletons.emplace_back(Skeleton());

		//Bone
		for (int i = 0; i < m_skeletons[k].GetBones().size(); ++i)
		{
			auto& bone = m_skeletons[k].GetBones()[i];
			
			GetAnimLocalBoneTransform(p_anim, i, k, posX, posY, posZ, quatW, quatX, quatY, quatZ);

			GPM::Matrix4<float> anim = GPM::Matrix4<float>::CreateTransformation(
				GPM::Vector3<float>{posX, posY, posZ},
				GPM::Quaternion{ quatX, quatY, quatZ, quatW },
				{ 1, 1, 1 });

			bone.SetLocalTransform(bone.GetLocalTPose() * anim);
		}
	}

	std::cout << "Animation nb of skeletons: " << m_skeletons.size() << std::endl;
}
