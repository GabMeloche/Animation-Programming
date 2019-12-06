#pragma once
#include "stdafx.h"
#include <Engine/Simulation.h>
#include <Engine/RenderingInfo.h>

class InputManager
{
public:
	InputManager() = delete;
	~InputManager() = delete;

	static void ProcessInputs(RenderingInfo& p_renderingInfo);
};

