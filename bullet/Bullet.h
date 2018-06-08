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
	Bullet(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef, float damage,
		Character* owner,bool centerOnEnnemy,bool towardEnnemy,std::shared_ptr<b2Shape> shape, std::chrono::milliseconds milliseconds)
		:Body(world, texture, myBodyDef,fixtureDef, shape), owner(owner), damage(damage)
		, centerOnEnnemy(centerOnEnnemy), towardEnnemy(towardEnnemy), elapsed(milliseconds){
		
		this->myBodyDef.userData = this;
		//myFixtureDef.userData = this;
	
	};
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

		return std::make_unique<Bullet>(*world, textureActuelle, myBodyDef, myFixtureDef, damage,
			owner, centerOnEnnemy, towardEnnemy,shape, elapsed);
	};
	virtual std::unique_ptr<Body> clone(Reflection& symetry);
	std::chrono::milliseconds& getElapsed() { return elapsed; };
	void setOwner(Character *ownere) { owner = ownere; };
	//std::map<Bullet, Reflection> & getBulletReflection() { return bulletReflection; };
	virtual void updateUserData() {
		myBodyDef.userData = this;

	}
private:
	float damage;
	Character* owner;
	bool toDelete=0;
	bool centerOnEnnemy;
	bool towardEnnemy;
//	int numeroReflection; // c'est egalement le numero de l'indice du boulet
	std::chrono::milliseconds elapsed;//temps nécessaire pour passer au suivant.
};

