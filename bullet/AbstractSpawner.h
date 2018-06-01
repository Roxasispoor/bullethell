#pragma once
#include "Body.h"
class AbstractSpawner : Body
{
public:
	AbstractSpawner(b2World &world):Body(world){};
	virtual ~AbstractSpawner();
};

