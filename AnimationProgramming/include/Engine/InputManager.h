#pragma once
#include "stdafx.h"
#include <Engine/Simulation.h>
#include <Engine/RenderingInfo.h>

class InputManager
{
public:
	InputManager() = default;
	~InputManager() = default;

	static void ProcessInputs(RenderingInfo& p_renderingInfo);
};

