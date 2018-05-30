#pragma once
#include "Character.h"
#include <vector>
#include <SFML/Audio.hpp>
class Ennemy :	public Character
{
public:
	
	Ennemy();
	~Ennemy();

private:
	sf::Music theme;
};

