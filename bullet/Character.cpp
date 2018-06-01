#include "stdafx.h"
#include "Character.h"


void Character::deleteAtEndStep()
{
	currentBullets.erase(
		std::remove_if(currentBullets.begin(), currentBullets.end(),
			[](const Bullet & o) { return o.getToDelete(); }),
		currentBullets.end());
}
void Character::preContact(Body * other)
{
	other->preContact(this);
}

void Character::postContact(Body * other)
{
	other->postContact(this);
}

void Character::shoot()
{
	patterns[chosenPattern].createShoot();

}

void Character::move()
{
	if (toGo.x != 0 && toGo.y != 0)
	{
		b2body->ApplyForce(b2Vec2(toGo.x * 100, toGo.y * 100), b2body->GetWorldCenter(), true);
	}
}
