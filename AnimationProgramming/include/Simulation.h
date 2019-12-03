#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "Engine.h"

class ENGINE_API ISimulation
{
public:
	virtual ~ISimulation() {}

	virtual void Init() {}
	virtual void Update( float frameTime ){}

	float m_timer = 0.0f;
};


#endif