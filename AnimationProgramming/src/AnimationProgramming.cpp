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
		skeleton = new Skeleton();
		
		int spine01 =	GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);
		std::cout << "NUMBER OF BONES: " << skeleton->GetBones().size();

		skeleton->AddAnimation("ThirdPersonWalk.anim", "Walk");
		skeleton->AddAnimation("ThirdPersonRun.anim", "Run");
	}

	
	virtual void Update(float frameTime) override
	{
		m_timer += frameTime * 10;
		skeleton->Animate(0, static_cast<int>(m_timer) % GetAnimKeyCount("ThirdPersonWalk.anim"));

		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);

		skeleton->DrawSkeleton({0, 1, 1});
		skeleton->DrawTPose({1, 0, 1});	
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

