#pragma once
#include "Body.h"
#include "Character.h"
#include <chrono>
#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Reflection.h"

class Character;
class Bullet :public Body
{
public:
	//SHAPE IS CLONED BY BOX2d
	//Bullet():Body(&new b2World(b2Vec2_zero)) { 	};
	Bullet(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef, float damage, Character* owner)
		:Body(world, texture, myBodyDef,fixtureDef), owner(owner), damage(damage) {};
	Bullet() = delete;
//	Bullet(const Bullet & truc) = delete;

	~Bullet();
	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual void startCollision(Character* other);
	virtual void endCollision(Character* other);
	bool getToDelete() const { return toDelete; };

	virtual std::unique_ptr<Body> clone()
	{

		return std::make_unique<Bullet>(*world, textureActuelle, myBodyDef, myFixtureDef, damage, owner);
	};
	virtual std::unique_ptr<Body> clone(Reflection& symetry);
	std::chrono::high_resolution_clock::duration& getElapsed() { return elapsed; };
	std::map<Bullet, Reflection> & getBulletReflection() { return bulletReflection; };
	
private:
	float damage;
	Character* owner;
	bool toDelete=0;
	std::map<Bullet, Reflection> bulletReflection;
	std::chrono::high_resolution_clock::duration elapsed;//temps nécessaire pour passer au suivant.
};

