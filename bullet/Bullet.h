#pragma once
#include "Body.h"
#include "Character.h"
class Bullet :
	public Body
{
public:
	Bullet();
	~Bullet();
	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual void startCollision(Character* other);
	virtual void endCollision(Character* other);
private:
	float damage;
	Character* owner;
};

