#pragma once
#include "Box2D/Box2D.h"
#include <vector>
/// <summary>
/// Possède 
/// </summary>
class Body
{
public:
	Body(b2World &world):world(world) {
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_kinematicBody;
	myBodyDef.position.Set(0, 0);
	b2Body* staticBody = world.CreateBody(&myBodyDef); };
	~Body();	
	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual void startCollision(Body* other);
	virtual void endCollision(Body* other);
private:
	b2Body* b2body;
	b2World &world;

	
};

