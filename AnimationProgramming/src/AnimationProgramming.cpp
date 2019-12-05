// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include <Engine/Engine.h>
#include <Engine/Simulation.h>
#include <Skeleton/Skeleton.h>
#include <Engine/InputManager.h>
#include "Windows.h"


class CSimulation : public ISimulation
{
public:
	Skeleton* skeleton = nullptr;
	InputManager inputManager;
	
	virtual void Init() override
	{
		skeleton = new Skeleton();
		//inputManager = new InputManager();
		int spine01 = GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);
		std::cout << "NUMBER OF BONES: " << skeleton->GetBones().size();

		skeleton->AddAnimation("ThirdPersonWalk.anim", "Walk");
		skeleton->AddAnimation("ThirdPersonRun.anim", "Run");
	}

	
	virtual void Update(float frameTime) override
	{		
		m_timer += frameTime * 20;

		inputManager.ProcessInputs();
		skeleton->Animate(inputManager.GetAnimationIndex(), m_timer);
		
		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);


		if (inputManager.GetDrawSkeleton())
			skeleton->DrawSkeleton({0, 1, 1});

		if (inputManager.GetDrawTPose())
			skeleton->DrawTPose({1, 0, 1});

	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

	delete simulation.skeleton;
    return 0;
}

