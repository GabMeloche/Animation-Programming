#pragma once
#include <GPM/GPM.h>

struct Transform
{
	GPM::Matrix4<float> m_matrix;
	GPM::Vector3<float> m_pos;
	GPM::Quaternion m_rot;
	GPM::Vector3<float> m_scale;
	
	inline void Update()
	{
		
	}
};

