#pragma once
#include "Character.h"
#include "AbstractSpawner.h"
#include "Bullet.h"
#include <vector>
#include <chrono>
class Bullet;
//Classe qui permet de charger en mémoire les pattern / les tirer
class Pattern:public AbstractSpawner
{
private:
	std::vector<Bullet> bullets; //ces bullets ont une fixture des et une body def mais pas d'existence physique

public:
	void createFromXml();//permet de charger les bullets en mémoire, mais n'instancie pas les objets physiques
	Pattern(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2CircleShape shape) :AbstractSpawner(world, texture, myBodyDef,shape) {};
	~Pattern();
	void createShoot();
	void updatePhysics();
	void activate(bool isRepeating)
	{
		isActivated = true;
		this->isRepeating = isRepeating;
	}
	void deleteAtEndStep();
private:
	std::chrono::high_resolution_clock::time_point timer;
	int bulletIndice = 0;
	bool isRepeating = false;
	std::vector<std::unique_ptr<Bullet>> currentBullets; //On évite ainsi le problème de downcast de uniqueptr. AT LEAST ONE MUST BE DIFFERENT FROM 0
	bool isActivated;
};

