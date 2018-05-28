#include "stdafx.h"
#include "Bullet.h"

void Bullet::preContact(Body * other)
{
	other->preContact(this);
}

void Bullet::postContact(Body * other)
{
	other->postContact(this);
}

/// <summary>
/// Starts the collision. Chacun est responsable de ses bullets!
/// </summary>
/// <param name="other">The other.</param>
void Bullet::startCollision(Character * other)
{
	if (other != owner)
	{
		owner->getToDelete().push_back(this);
	}
}

Bullet::~Bullet()
{
}
