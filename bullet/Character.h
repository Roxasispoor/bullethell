#pragma once
#include "Bullet.h"
#include "Pattern.h"
#include "Command.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Bullet;
class Pattern;
class Command;
class Character:public Body
{
public:
	Character(b2World &world) :Body(world) {};
	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual ~Character();
	virtual void shoot();//crache un pattern
	void bright();
	virtual void onDeath();
	virtual void move();
	std::vector<Bullet>& getCurrentBullets() {
		return currentBullets;
	}
	
	void deleteAtEndStep();
private:
	const float multiplierMove=1;
	float vieMax;
	float vieActuelle;
	std::vector<Bullet> currentBullets;
		//std::vector<Bullet*> toDelete;// supprimer et clear a la fin
protected:
	std::vector<std::unique_ptr<Command>> commands;
	b2Vec2 toGo;
	bool focus;
	int chosenPattern;
	std::vector<Pattern> patterns;
};

