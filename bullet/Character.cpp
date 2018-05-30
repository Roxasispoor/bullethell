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
