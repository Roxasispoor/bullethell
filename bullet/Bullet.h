#pragma once
#include "Body.h"
#include "Character.h"
#include <chrono>

class Character;
class Bullet :public Body
{
public:
	//Bullet():Body(&new b2World(b2Vec2_zero)) { 	};
	Bullet(b2World &world) :Body(world) {};
	Bullet() = delete;
	~Bullet();
	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual void startCollision(Character* other);
	virtual void endCollision(Character* other);
	bool getToDelete() const{ return toDelete; };
	virtual std::unique_ptr<Body> clone()
	{
		return std::make_unique<Bullet>(*world);
	};
private:
	float damage;
	Character* owner;
	bool toDelete;
	std::chrono::duration<double> elapsed;//temps nécessaire pour passer au suivant
};

