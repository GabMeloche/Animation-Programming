#pragma once

#include "stdafx.h"
#include "Simulation.h"
#include <Bone.h>
#include <vector>

class Skeleton
{
public:
	Skeleton(const char* p_anim);
	~Skeleton() = default;

	inline std::vector<Bone>& GetBones() { return m_bones; }
	inline void AddBone(Bone& p_bone) { m_bones.emplace_back(p_bone); }
	
	void DrawSkeleton();
	void UpdateSkeleton();
	void UpdateBones(Bone* p_bone);
	void PrintSkeleton();
	
private:
	std::vector<Bone> m_bones;
	Bone* m_root;
};

