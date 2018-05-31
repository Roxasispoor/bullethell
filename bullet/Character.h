#pragma once
#include "Bullet.h"
#include "Pattern.h"
#include "Command.h"
#include <iostream>
#include <SFML/Graphics.hpp>
class Bullet;
class Pattern;
class Command;
class Character:Body
{
public:
	Character();
	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual ~Character();
	virtual void shoot();//crache un pattern
	virtual void onDeath();
	std::vector<Bullet>& getCurrentBullets() {
		return currentBullets;
	}
	
	void deleteAtEndStep();
private:
	std::vector<Pattern> patterns;
	float vieMax;
	float vieActuelle;
	std::vector<Bullet> currentBullets;
	//std::vector<Bullet*> toDelete;// supprimer et clear a la fin
protected:
	std::unique_ptr<Command> command;

};

