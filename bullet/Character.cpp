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
}

void Character::shoot()
{
	patterns[chosenPattern].activate(false);

}

void Character::move()
{
	if (toGo.x != 0 && toGo.y != 0)
	{
		b2body->ApplyForce(b2Vec2(toGo.x * 100, toGo.y * 100), b2body->GetWorldCenter(), true);
	}
}
