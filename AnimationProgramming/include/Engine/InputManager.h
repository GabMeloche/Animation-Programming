#pragma once
#include "stdafx.h"

class InputManager
{
public:
	InputManager(): m_drawTPose{false}, m_drawSkeleton{false}, m_animationIndex{-1} {}
	~InputManager() = default;

	void ProcessInputs();

	inline bool GetDrawTPose() const { return m_drawTPose; }
	inline bool GetDrawSkeleton() const { return m_drawSkeleton; }
	inline int GetAnimationIndex() const { return m_animationIndex; }
	
private:
	bool m_drawTPose;
	bool m_drawSkeleton;
	int m_animationIndex;
};

