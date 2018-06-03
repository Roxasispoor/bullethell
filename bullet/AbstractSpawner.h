#pragma once
#include "Body.h"
class AbstractSpawner : public Body
{
public:
	AbstractSpawner(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2CircleShape shape) :Body(world, texture, myBodyDef, shape) {};
	virtual ~AbstractSpawner();
};

