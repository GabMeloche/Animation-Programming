#pragma once
#include "stdafx.h"


class Skeleton;

class Animation
{
public:
	Animation(const char* p_anim, const char* p_name);
	~Animation() = default;

	inline std::vector<Skeleton>& GetSkeletons() { return m_skeletons; }

private:
	std::vector<Skeleton> m_skeletons;
	std::string m_name;
};
