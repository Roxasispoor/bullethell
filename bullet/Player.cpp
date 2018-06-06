#include "stdafx.h"
#include "Player.h"
#include "Command.h"


void Player::input()
{
	toGo.x = 0;
	toGo.y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
	//	Command test((Character*)this, &Character::shoot);
		toGo.x-=1;
		//std::cout << "AAAAAAAAAAAAAAAAAAAH";
		// move left...
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		toGo.x += 1;
		// move right...
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		toGo.y += 1;
		// move right...
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		toGo.y -= 1;
		// move right...
	}
	commands.push_back(Command(this, &Character::move));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		commands.push_back(Command(this, &Character::shoot));

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		focus = true;
		multiplierMove = 0.5;
	//	commands.push_back(Command(this, &Character::bright));
	}
	else
	{
		focus = false;
		multiplierMove = 1;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))//switch arms
	{
			chosenPattern += 1 % patterns.size();

		}
}

