#include "stdafx.h"
#include "Player.h"



void Player::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		command.execute();
		// move left...
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// move right...
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		// quit...
	}

}

Player::Player()
{
}


Player::~Player()
{
}
