// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include <Engine.h>
#include <Simulation.h>
#include <Skeleton/Skeleton.h>
#include "Windows.h"


class CSimulation : public ISimulation
{
public:
	Skeleton* skeleton = nullptr;
	
	virtual void Init() override
	{
		skeleton = new Skeleton();
		
		int spine01 = GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);
		std::cout << "NUMBER OF BONES: " << skeleton->GetBones().size();

		skeleton->AddAnimation("ThirdPersonWalk.anim", "Walk");
		skeleton->AddAnimation("ThirdPersonRun.anim", "Run");
	}

	
	virtual void Update(float frameTime) override
	{
		static int animation = -1;
		static bool drawSkeleton = false;
		static bool drawTPose = false;
		
		m_timer += frameTime * 20;

		skeleton->Animate(animation, m_timer);
		
		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);


		if (drawSkeleton)
			skeleton->DrawSkeleton({0, 1, 1});

		if (drawTPose)
			skeleton->DrawTPose({1, 0, 1});

		if (GetAsyncKeyState('F') & 0x1)
		{
			++animation;
			if (animation >= skeleton->GetAnimations().size())
				animation = -1;
		}
		
		if (GetAsyncKeyState('Z') & 0x1)
		{
			drawSkeleton = !drawSkeleton;
		}
		
		if (GetAsyncKeyState('X') & 0x1)
		{
			drawTPose = !drawTPose;
		}
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

	delete simulation.skeleton;
    return 0;
}

