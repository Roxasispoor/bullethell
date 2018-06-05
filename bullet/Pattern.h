#pragma once
#include "Character.h"
#include "AbstractSpawner.h"
#include "Bullet.h"
#include <vector>
#include "Reflection.h"
#include <chrono>
class Bullet;
//Classe qui permet de charger en mémoire les pattern / les tirer
class Pattern:public AbstractSpawner
{
private:
	
public:
	void createFromXml();//permet de charger les bullets en mémoire, mais n'instancie pas les objets physiques
	Pattern(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef) :AbstractSpawner(world, texture, myBodyDef, fixtureDef) {};
	~Pattern();
	void createShoot();
	void updatePhysics();
	void activate(bool isRepeating)
	{
		isActivated = true;
		this->isRepeating = isRepeating;
	}
	void deleteAtEndStep();
	virtual std::unique_ptr<Body> clone()
	{
		return std::make_unique<Pattern>(*world, textureActuelle, myBodyDef, myFixtureDef);
	};
	/*Pattern(Pattern& const pattern) :Pattern(*pattern.world, pattern.textureActuelle, pattern.myBodyDef, pattern.myFixtureDef){	
	
	}*/
private:

	std::vector<Bullet> bullets; //ces bullets ont une fixture des et une body def mais pas d'existence physique
	std::vector<std::shared_ptr<Reflection>> reflections;
	std::chrono::high_resolution_clock::time_point timer;
	int bulletIndice = 0;
	bool isRepeating = false;
	std::vector<Bullet> currentBullets; //On évite ainsi le problème de downcast de uniqueptr. AT LEAST ONE MUST BE DIFFERENT FROM 0
	bool isActivated;
};

