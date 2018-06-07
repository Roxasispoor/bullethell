#pragma once
#include "Character.h"
/// <summary>
/// Character qui peut recevoir les input utilisateurs + mana et autres.
/// </summary>
/// <seealso cref="Character" />
class Player :
	public Character
{
public:
	void input();
	void update();
	Player(b2World &world, sf::Texture* texture, b2BodyDef myBodyDef, b2FixtureDef fixtureDef, std::shared_ptr<b2Shape> shape) :
		Character(world, texture, myBodyDef, fixtureDef,shape) {};
	//~Player();
	virtual std::unique_ptr<Body> clone()
	{
		return std::make_unique<Player>(*world,textureActuelle,myBodyDef, myFixtureDef,shape);
	};
};

