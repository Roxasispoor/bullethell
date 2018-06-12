#pragma once
#include "Character.h"

#include "Bullet.h"
#include <vector>
#include "Reflection.h"
#include <chrono>
#include <pugixml.hpp>
#include <iostream>
 
class Bullet;
class Character;
//Classe qui permet de charger en mémoire les pattern / les tirer
class Pattern:public Body
{


public:	
	/// <summary>
	/// Creates from XML bullets.
	/// </summary>
	/// <param name="patternNode">The pattern node.</param>
	/// <param name="textureMap">The texture map.</param>
	void createFromXml(pugi::xml_node patternNode, std::map<std::string, sf::Texture> &textureMap);
	
	Pattern(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef, std::shared_ptr<b2Shape> shape) :
		Body(world, texture, myBodyDef, fixtureDef,shape) {
			
	};

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
	std::chrono::system_clock::time_point& getTimer() { return timer; };
	void setTimerNow() { timer = std::chrono::system_clock::now(); };
	bool getIsActivated() { return isActivated; };
	virtual void draw(sf::RenderWindow& window);
	
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
	b2Vec2 position;
	float angle;
	//pugi::xml_node doc;
};

