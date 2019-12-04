#pragma once

#include "stdafx.h"
#include "Simulation.h"
#include <Bone.h>
#include <vector>

class Skeleton
{
public:
	Skeleton();
	~Skeleton() = default;

	inline std::vector<Bone>& GetBones() { return m_bones; }
	inline void AddBone(Bone& p_bone) { m_bones.emplace_back(p_bone); }
	
	void DrawSkeleton(const GPM::Vector3F& p_color);
	void DrawTPose(const GPM::Vector3F& p_color);
	void ComputeSkeleton();
	void CalculateBoneInverses();
	void ComputeBones(Bone* p_bone);
	void PrintSkeleton();
	void Animate(const char* p_anim, int p_frame);
	
private:
	std::vector<Bone> m_bones;
	Bone* m_root;
};

