#pragma once
#include "stdafx.h"
#include <Animation/AnimSkeleton.h>

class Skeleton;

class Animation
{
public:
	Animation(const char* p_anim, const char* p_name);
	~Animation() = default;

	inline std::vector<AnimSkeleton>& GetAnimSkeletons() { return m_animSkeletons; }

private:
	std::vector<AnimSkeleton> m_animSkeletons;
	std::string m_name;
};
