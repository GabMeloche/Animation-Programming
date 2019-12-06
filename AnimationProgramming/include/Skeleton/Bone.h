#pragma once
#include "stdafx.h"

class Bone
{
public:
	Bone() = default;
	Bone(const GPM::Vector3<float>& p_pos, const GPM::Quaternion& p_quat)
	{
		m_localTransform = GPM::Matrix4<float>::CreateTransformation(p_pos, p_quat, { 1, 1, 1 });
		m_localTPose = m_localTransform;
	}
	
	~Bone() = default;

	inline Bone* GetParent() const { return m_parent; }
	inline void SetParent(Bone* p_parent) { m_parent = p_parent; }

	inline std::string& GetName() { return m_name; }
	inline void SetName(const std::string& p_name) { m_name = p_name; }

	inline std::vector<Bone*>& GetChildren() { return m_children; }
	inline void EmplaceBackChildren(Bone* p_child) { m_children.emplace_back(p_child); }

	inline GPM::Matrix4<float>& GetLocalTransform() { return m_localTransform; }
	inline void SetLocalTransform(const GPM::Matrix4<float>& p_other) { m_localTransform = p_other; }
	
	inline GPM::Matrix4<float>& GetWorldTransform() { return m_worldTransform; }
	inline void SetWorldTransform(const GPM::Matrix4<float>& p_other) { m_worldTransform = p_other; }

	inline GPM::Matrix4<float>& GetLocalTPose() { return m_localTPose; }
	inline void SetLocalTPose(const GPM::Matrix4<float>& p_other) { m_localTPose = p_other; }
	
	inline GPM::Matrix4<float>& GetWorldTPose() { return m_WorldTPose; }
	inline void SetWorldTPose(const GPM::Matrix4<float>& p_other) { m_WorldTPose = p_other; }
	
	
private:
	Bone* m_parent = nullptr;
	std::string m_name;
	std::vector<Bone*> m_children;

	GPM::Matrix4<float> m_localTransform;
	GPM::Matrix4<float> m_worldTransform;
	GPM::Matrix4<float> m_localTPose;
	GPM::Matrix4<float> m_WorldTPose;
	
};
