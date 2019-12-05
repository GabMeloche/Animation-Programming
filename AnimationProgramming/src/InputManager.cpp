#include <Engine/InputManager.h>
#include "Windows.h"

void InputManager::ProcessInputs()
{
	if (GetAsyncKeyState('F') & 0x1)
	{
		++m_animationIndex;
		if (m_animationIndex > 1)
			m_animationIndex = -1;

		std::cout << "animation index unputmanager: " << m_animationIndex << std::endl;
	}

	if (GetAsyncKeyState('Z') & 0x1)
	{
		m_drawSkeleton = !m_drawSkeleton;
	}

	if (GetAsyncKeyState('X') & 0x1)
	{
		m_drawTPose = !m_drawTPose;
	}
}

