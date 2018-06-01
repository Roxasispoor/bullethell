#pragma once
#include <vector>
#include <SFML/Audio.hpp>
#include "Body.h"
#include "Character.h"
class Character;

class Ennemy :	public Character
{
public:
	
	Ennemy(b2World &world) :Character(world) {};
	~Ennemy();
	virtual std::unique_ptr<Body> clone()
	{
		return std::make_unique<Ennemy>(*world);
	};
private:
	sf::Music theme;
};

