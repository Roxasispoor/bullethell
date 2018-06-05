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
void Character::updatePhysics()
{

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
	
		b2body->SetLinearVelocity(b2Vec2(toGo.x*speedFrame , toGo.y*speedFrame));
	
}
