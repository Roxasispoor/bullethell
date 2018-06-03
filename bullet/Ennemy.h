#pragma once
#include <vector>
#include <SFML/Audio.hpp>
#include "Body.h"
#include "Character.h"
class Character;

class Ennemy :	public Character
{
public:
	
	Ennemy(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2CircleShape shape) :Character(world, texture, myBodyDef,shape) {};
	~Ennemy();
	virtual std::unique_ptr<Body> clone()
	{
		return std::make_unique<Ennemy>(*world,textureActuelle,myBodyDef, shape);
	};
private:
	sf::Music theme;
};

