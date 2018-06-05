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
		toDelete = true;
			
	}
}

void Bullet::endCollision(Character * other)
{
}

std::unique_ptr<Body> Bullet::clone(Reflection& symetry)
{
	b2BodyDef bodydef(myBodyDef);
	symetry.applyReflection(bodydef); //On le modifie comme il faut
	return std::make_unique<Bullet>(*world, textureActuelle,bodydef, myFixtureDef, damage, owner);
}

Bullet::~Bullet()
{
}
