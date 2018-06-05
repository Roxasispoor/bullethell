#pragma once
#include "Bullet.h"
#include "Pattern.h"
#include <iostream>
#include "Command.h"
#include <queue>
#include <SFML/Graphics.hpp>
#include "const.h"
class Bullet;
class Pattern;
class Command;
class Character:public Body
{
public:
	Character(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef):
		Body(world,texture,myBodyDef,fixtureDef) {
		chosenPattern = 0;
	};

	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	//virtual ~Character();
	virtual void updatePhysics();
	virtual void shoot();//crache un pattern
	void bright();
	virtual void onDeath();
	virtual void move();
	

private:
	const float multiplierMove=1;
	float vieMax;
	float vieActuelle;
protected:
	float speedFrame = 0.1*FPS;
	std::deque<Command> commands;
	b2Vec2 toGo;
	bool focus;
	int chosenPattern;
	std::vector<Pattern> patterns;
};

