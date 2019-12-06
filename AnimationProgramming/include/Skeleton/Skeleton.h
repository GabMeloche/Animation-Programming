#pragma once

#include "stdafx.h"
#include <Skeleton/Bone.h>
#include <Animation/Animation.h>

class Skeleton
{
public:
	Skeleton();
	~Skeleton() = default;

	
	void DrawSkeleton(const GPM::Vector3F& p_color);
	void DrawTPose(const GPM::Vector3F& p_color);
	void ComputeSkeleton();
	void ComputeBones(Bone* p_bone);
	void PrintSkeleton();
	void Animate(int p_animationIndex, float p_time, float p_animSpeed);

	std::vector<Animation>& GetAnimations() { return m_animations; }
	void AddAnimation(const char* p_anim, const char* p_name);
	
	inline std::vector<Bone>& GetBones() { return m_bones; }
	inline void AddBone(Bone& p_bone) { m_bones.emplace_back(p_bone); }
	
private:
	std::vector<Animation> m_animations;
	std::vector<Bone> m_bones;
	Bone* m_root;
};

