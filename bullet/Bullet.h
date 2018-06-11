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
		//*this = other; => JE le laisse pour les perles des bugs qui sont longs, chiants a débuggers et non verbeux
		shape = other.shape;
		fixture = other.fixture;
		textureActuelle = other.textureActuelle;
		myBodyDef = other.myBodyDef;
		myFixtureDef = other.myFixtureDef;
		b2body = other.b2body;
		world = other.world;
		hitbox = other.hitbox;
		drawHitBox = other.drawHitBox;
		screenWidth = other.screenWidth;
		sprite = other.sprite;
		spriteWidth = other.spriteWidth;
		spriteHeight = other.spriteHeight;
		currentstate = other.currentstate;
		hauteurInSprite = other.hauteurInSprite;
		currentID = ID++;

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
	bool toDelete=0;
	bool centerOnEnnemy;
	bool towardEnnemy;
	
//	int numeroReflection; // c'est egalement le numero de l'indice du boulet
	std::chrono::milliseconds elapsed;//temps nécessaire pour passer au suivant.
};

