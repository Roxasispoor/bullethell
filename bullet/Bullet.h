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
	Bullet(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef, float damage,
		Character* owner,bool centerOnEnnemy,bool towardEnnemy,std::shared_ptr<b2Shape> shape,
		std::chrono::milliseconds milliseconds)
		:Body(world, texture, myBodyDef,fixtureDef, shape), owner(owner), damage(damage)
		, centerOnEnnemy(centerOnEnnemy), towardEnnemy(towardEnnemy), elapsed(milliseconds) {
		sprite.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	};
	Bullet() = delete;
	Bullet &operator=(Bullet other);
	
	virtual void preContact(Body* other) override;// Implementation patron multi dispatcher celui-ci 
	virtual void preContact(Character* other);
	virtual void preContact(Bullet* other) override;



	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	
	virtual void startCollision(Character* other);
	virtual void endCollision(Character* other);
	
	bool getToDelete() const { return toDelete; };
	/// <summary>
	/// Clones this instance. Inusité
	/// </summary>
	/// <returns></returns>
	virtual std::unique_ptr<Body> clone()
	{

		return std::make_unique<Bullet>(*world, textureActuelle, myBodyDef, myFixtureDef, damage,
			owner, centerOnEnnemy, towardEnnemy,shape, elapsed);
	};
	virtual std::unique_ptr<Body> clone(Reflection& symetry);
	std::chrono::milliseconds& getElapsed() { return elapsed; };
	void setOwner(Character *ownere) { owner = ownere; };

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
	std::chrono::milliseconds elapsed;//temps nécessaire pour passer au suivant.
};

