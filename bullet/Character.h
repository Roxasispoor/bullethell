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
	Character(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef, 
		std::shared_ptr<b2Shape> shape, float lifemax):
		Body(world,texture,myBodyDef,fixtureDef,shape),timePassNext(0.5),accumulated(0),vieMax(lifemax),vieActuelle(lifemax) {
		
		chosenPattern = 0;
	};

	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void preContact(Bullet* bullet);
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual void startCollision(Bullet* other);
										  //virtual ~Character();
	virtual void updatePhysics(std::chrono::duration<double> elapsed);
	virtual void shoot();//crache un pattern
	void bright();
	virtual void updateUserData() {
		myBodyDef.userData = this;
	}
	virtual void onDeath();
	virtual void move();
	std::vector<Pattern>& getPatterns() { return patterns; };
	virtual void draw(sf::RenderWindow& window);
	
protected:

	float vieMax;
	float vieActuelle;

	float multiplierMove = 1;
	float speedFrame = 0.6*FPS;
	std::chrono::duration<double> timePassNext;
	std::chrono::duration<double> accumulated;
	
	int numberState = 3;
	std::deque<Command> commands;
	b2Vec2 toGo;
	bool focus;
	int chosenPattern;
	std::vector<Pattern> patterns;
	
};

