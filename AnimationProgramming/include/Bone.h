#pragma once
#include "stdafx.h"

class Bone
{
public:
	Bone() = default;
	Bone(const GPM::Vector3<float>& p_pos, const GPM::Quaternion& p_quat) : m_localPos{ p_pos }, m_rot { m_rot } {}
	~Bone() = default;

	inline void SetLocalPos(GPM::Vector3<float>& p_pos) { m_localPos = p_pos; }
	inline GPM::Vector3<float>& GetLocalPos() { return m_localPos; }

	inline void SetWorldPos(GPM::Vector3<float>& p_pos) { m_worldPos = p_pos; }
	inline GPM::Vector3<float>& GetWorldPos() { return m_worldPos; }

	inline Bone* GetParent() const { return m_parent; }
	inline void SetParent(Bone* p_parent) { m_parent = p_parent; }

	inline GPM::Quaternion& GetRotation() { return m_rot; }
	inline void SetRotation(GPM::Quaternion& p_rot) { m_rot = p_rot; }

	inline std::string& GetName() { return m_name; }
	inline void SetName(const std::string& p_name) { m_name = p_name; }

	inline std::vector<Bone*>& GetChildren() { return m_children; }
	inline void EmplaceBackChildren(Bone* p_child) { m_children.emplace_back(p_child); }
	
private:
	Bone* m_parent = nullptr;
	std::vector<Bone*> m_children;
	GPM::Vector3<float> m_localPos{0, 0, 0};
	GPM::Vector3<float> m_worldPos{0, 0, 0};
	GPM::Quaternion m_rot;
	std::string m_name;

	GPM::Matrix4<float> m_localTransform;
	GPM::Matrix4<float> m_worldTransform;
};
