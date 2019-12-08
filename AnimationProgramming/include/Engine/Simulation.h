#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <Engine/Engine.h>

class ENGINE_API ISimulation
{
public:
	virtual ~ISimulation() = 0;

	virtual void Init() = 0;
	
	virtual void Update(const float p_frameTime) = 0;
};


#endif