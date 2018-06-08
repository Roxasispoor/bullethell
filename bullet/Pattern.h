#pragma once
#include "Character.h"
#include "AbstractSpawner.h"
#include "Bullet.h"
#include <vector>
#include "Reflection.h"
#include <chrono>
#include <pugixml.hpp>
#include <iostream>
 
class Bullet;
class Character;
//Classe qui permet de charger en mémoire les pattern / les tirer
class Pattern:public AbstractSpawner
{


public:
	void createFromXml(pugi::xml_node patternNode, std::map<std::string, sf::Texture> &textureMap);
	//permet de charger les bullets en mémoire, mais n'instancie pas les objets physiques
	Pattern(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef, std::shared_ptr<b2Shape> shape) :
		AbstractSpawner(world, texture, myBodyDef, fixtureDef,shape) {
			
	};
	//~Pattern();
	void setOwner(Character* ownere) { owner = ownere; }
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
		return std::make_unique<Pattern>(*world, textureActuelle, myBodyDef, myFixtureDef,shape);
	};
	//void setTimer(std::chrono::high_resolution_clock::time_point timerino) { timer = timerino; };
	/*Pattern(Pattern& const pattern) :Pattern(*pattern.world, pattern.textureActuelle, pattern.myBodyDef, pattern.myFixtureDef){	
	
	}*/
	std::chrono::system_clock::time_point& getTimer() { return timer; };
	void setTimerNow() { timer = std::chrono::system_clock::now(); };
	bool getIsActivated() { return isActivated; };
	virtual void draw(sf::RenderWindow& window);
	virtual void updateUserData() {
		myBodyDef.userData = this;
	}
private:

	std::vector<Bullet> bullets; //ces bullets ont une fixture des et une body def mais pas d'existence physique
	std::vector<std::shared_ptr<Reflection>> reflections;
	std::chrono::system_clock::time_point timer;
	Character *owner;
	int bulletIndice = 0;
	bool isRepeating = false;
	//int symetryIndice = 0;
	std::vector<std::vector<Bullet>> currentBullets; //On évite ainsi le problème de downcast de uniqueptr. AT LEAST ONE MUST BE DIFFERENT FROM 0
	bool isActivated;
	//pugi::xml_node doc;
};

