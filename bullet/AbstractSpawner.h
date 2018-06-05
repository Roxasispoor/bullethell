#pragma once
#include "Body.h"
class AbstractSpawner : public Body
{
public:
	AbstractSpawner(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef) :
		Body(world, texture, myBodyDef, fixtureDef) {};
	virtual ~AbstractSpawner();
};

