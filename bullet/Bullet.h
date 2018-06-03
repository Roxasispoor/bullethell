#pragma once
#include "Body.h"
#include "Character.h"
#include <chrono>
#include "Box2D/Collision/Shapes/b2Shape.h"

class Character;
class Bullet :public Body
{
public:
	//Bullet():Body(&new b2World(b2Vec2_zero)) { 	};
	Bullet(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2CircleShape shape,float damage, Character* owner)
		:Body(world, texture, myBodyDef,shape),owner(owner),damage(damage) {};
	Bullet() = delete;
	~Bullet();
	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual void startCollision(Character* other);
	virtual void endCollision(Character* other);
	bool getToDelete() const{ return toDelete; };
	virtual std::unique_ptr<Body> clone()
	{
	
		return std::make_unique<Bullet>(*world,textureActuelle,myBodyDef, shape,damage,owner);
	};
	std::chrono::high_resolution_clock::duration& getElapsed(){ return elapsed; };
	
private:
	float damage;
	Character* owner;
	bool toDelete=0;

	std::chrono::high_resolution_clock::duration elapsed;//temps nécessaire pour passer au suivant.
};

