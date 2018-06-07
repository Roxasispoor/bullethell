#pragma once
#include "Body.h"
class AbstractSpawner : public Body
{
public:
	AbstractSpawner(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef, std::shared_ptr<b2Shape> shape) :
		Body(world, texture, myBodyDef, fixtureDef,shape) {};
	virtual ~AbstractSpawner();
};

