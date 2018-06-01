#pragma once
#include "stdafx.h"
#include "Box2D/Box2D.h"
#include <vector>
/// <summary>
/// Possède un corps physique 
/// </summary>
class Body
{
public:

	Body(b2World &world):world(&world) 
	{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_kinematicBody;
	myBodyDef.position.Set(0, 0);
	b2Body* staticBody = world.CreateBody(&myBodyDef); 
	};
	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual void startCollision(Body* other);
	virtual void endCollision(Body* other);
	virtual std::unique_ptr<Body> clone() = 0;
	~Body()
	{
		world->DestroyBody(b2body); //On détruit le body dans le world
	}
	
private: 
	
	//implement Ball class destructor
protected:
	b2Body * b2body;
	b2World *world;

};

