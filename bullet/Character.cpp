#include "stdafx.h"
#include "Character.h"

void Character::preContact(Body * other)
{
	other->preContact(this);
}

void Character::postContact(Body * other)
{
	other->postContact(this);
}

/// <summary>
/// Updates the physics of the character. Main loop
/// </summary>
void Character::updatePhysics(std::chrono::duration<double> elapsed)
{
	accumulated += elapsed;
	if (accumulated > timePassNext)
	{
		accumulated -= timePassNext;
		currentstate = (currentstate + 1) % numberState;
		sprite.setTextureRect(sf::IntRect(currentstate*spriteWidth, 0, spriteWidth, spriteHeight));
	}
	for (auto &p : patterns)
	{
		p.updatePhysics();
	}
	while (!commands.empty()) //on fait toutes les commandes
	{
		commands.front().execute();
		commands.pop_front();
	}
}

void Character::shoot()
{
	if (patterns.size() > 0)
	{
		patterns[chosenPattern].activate(false);
	}
}

void Character::bright()
{
}

void Character::onDeath()
{
}

void Character::move()
{
	
	toGo.Normalize();
	b2body->SetLinearVelocity(b2Vec2(toGo.x*speedFrame*multiplierMove , toGo.y*speedFrame*multiplierMove));
	
}

