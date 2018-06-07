#pragma once
#include <vector>
#include <SFML/Audio.hpp>
#include "Body.h"
#include "Character.h"
class Character;

class Ennemy :	public Character
{
public:
	
	Ennemy(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef, std::shared_ptr<b2Shape> shape) :
		Character(world, texture, myBodyDef, fixtureDef,shape) { hauteurInSprite = 2; };
	~Ennemy();
	virtual std::unique_ptr<Body> clone()
	{
		return std::make_unique<Ennemy>(*world,textureActuelle,myBodyDef, myFixtureDef,shape);
	};
private:
//	sf::Music theme;
};

