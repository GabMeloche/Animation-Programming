#include <Engine/InputManager.h>
#include "Windows.h"

void InputManager::ProcessInputs(RenderingInfo& p_renderingInfo)
{
	if (GetAsyncKeyState('F') & 0x1)
	{
		++p_renderingInfo.m_animationIndex;
		
		if (p_renderingInfo.m_animationIndex > 1)
			p_renderingInfo.m_animationIndex = -1;
	}

	if (GetAsyncKeyState('Z') & 0x1)
	{
		p_renderingInfo.m_drawSkeleton = !p_renderingInfo.m_drawSkeleton;
	}

	if (GetAsyncKeyState('X') & 0x1)
	{
		p_renderingInfo.m_drawTPose = !p_renderingInfo.m_drawTPose;
	}
	
	if (GetAsyncKeyState(VK_UP) & 0x1)
	{
		p_renderingInfo.m_animSpeed += 0.1f;
		std::cout << "Animation speed: " << p_renderingInfo.m_animSpeed << std::endl;
	}
	
	if (GetAsyncKeyState(VK_DOWN) & 0x1)
	{
		p_renderingInfo.m_animSpeed -= 0.1f;
		std::cout << "Animation speed: " << p_renderingInfo.m_animSpeed << std::endl;
	}
}