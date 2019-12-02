// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "Engine.h"
#include "Simulation.h"
#include "Skeleton.h"



class CSimulation : public ISimulation
{
	
	Skeleton* skeleton = nullptr;
	
	virtual void Init() override
	{
		skeleton = new Skeleton("ThirdPersonWalk.anim");
		
		int spine01 =	GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);
		
		skeleton->PrintSkeleton();
	}

	
	virtual void Update(float frameTime) override
	{

		
		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);

		skeleton->DrawSkeleton();
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

