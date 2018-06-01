#include "stdafx.h"
#include "Player.h"
#include "Command.h"


void Player::input()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
	//	Command test((Character*)this, &Character::shoot);
		toGo.x=-1;
		
		// move left...
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		toGo.x = 1;
		// move right...
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		toGo.y = 1;
		// move right...
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		toGo.x = 1;
		// move right...
	}
	commands.push_back(std::make_unique<Command>(this, &Character::move));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		commands.push_back(std::make_unique<Command>(this, &Character::shoot));

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		focus = true;
		commands.push_back(std::make_unique<Command>(this, &Character::bright));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))//switch arms
	{
			chosenPattern += 1 % patterns.size();

		}
}

