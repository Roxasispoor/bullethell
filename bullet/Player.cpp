#include "stdafx.h"
#include "Player.h"
#include "Command.h"


void Player::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
	//	Command test((Character*)this, &Character::shoot);
		command = std::make_unique<Command>(this, &Character::shoot);
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
