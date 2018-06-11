#pragma once
#include "Body.h"
#include "Character.h"
#include <chrono>
#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Reflection.h"

class Character;
class Bullet;
class Bullet :public Body
{
public:
	//SHAPE IS CLONED BY BOX2d
	//Bullet():Body(&new b2World(b2Vec2_zero)) { 	};
	Bullet(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef, float damage,
		Character* owner,bool centerOnEnnemy,bool towardEnnemy,std::shared_ptr<b2Shape> shape,
		std::chrono::milliseconds milliseconds)
		:Body(world, texture, myBodyDef,fixtureDef, shape), owner(owner), damage(damage)
		, centerOnEnnemy(centerOnEnnemy), towardEnnemy(towardEnnemy), elapsed(milliseconds) {
		
		
		//identifiant++;
		
		
	};
	Bullet() = delete;
//	Bullet(const Bullet & truc) = delete;
	Bullet &operator=(Bullet other)
	{
		//*this = other; => JE le laisse pour les perles des bugs qui sont longs, chiants a d�buggers et non verbeux
		
		damage = other.damage;
		owner = other.owner;
		toDelete = other.toDelete;
		centerOnEnnemy = other.centerOnEnnemy;
		towardEnnemy = other.towardEnnemy;

		//	int numeroReflection; // c'est egalement le numero de l'indice du boulet
		 elapsed=other.elapsed;


		Body::operator=(other);
		

	//	currentID = other.currentID;

		myBodyDef.userData = this;
		if (b2body)
		{
			b2body->SetUserData(this);
		}

		return *this;
	}
	
	virtual void preContact(Body* other) override;// Implementation patron multi dispatcher celui-ci 
	virtual void preContact(Character* other);
	virtual void preContact(Bullet* other) override;



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

	void setToDelete(bool toD) { toDelete = toD; };
	Character* getOwner() {	return owner;};
	float getDamage() { return damage; };
	void getSureNoBody() { b2body = nullptr;
	fixture = nullptr;
	}
private:
	float damage;
	Character* owner;
	bool toDelete=false;
	bool centerOnEnnemy;
	bool towardEnnemy;
	
//	int numeroReflection; // c'est egalement le numero de l'indice du boulet
	std::chrono::milliseconds elapsed;//temps n�cessaire pour passer au suivant.
};

