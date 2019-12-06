// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include <Engine/Engine.h>
#include <Engine/Simulation.h>
#include <Skeleton/Skeleton.h>
#include <Engine/InputManager.h>
#include <Engine/RenderingInfo.h>
#include <memory>
#include "Windows.h"


class CSimulation : public ISimulation
{
private:
	std::unique_ptr<Skeleton> m_skeleton = nullptr;
	RenderingInfo m_renderingInfo;
	
public:
	virtual void Init() override
	{
		m_skeleton = std::make_unique<Skeleton>();

		m_skeleton->AddAnimation("ThirdPersonWalk.anim", "Walk");
		m_skeleton->AddAnimation("ThirdPersonRun.anim", "Run");
	}

	
	virtual void Update(float frameTime) override
	{		
		m_timer += frameTime;

		InputManager::ProcessInputs(m_renderingInfo);

		m_skeleton->Animate(m_renderingInfo.m_animationIndex, m_timer, m_renderingInfo.m_animSpeed);
		
		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);


		if (m_renderingInfo.m_drawSkeleton)
			m_skeleton->DrawSkeleton({0, 1, 1});

		if (m_renderingInfo.m_drawTPose)
			m_skeleton->DrawTPose({1, 0, 1});

	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

