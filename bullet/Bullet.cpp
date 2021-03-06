#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"

bool operator==(const Bullet & left, const Bullet & right)
{

	return left.getCurrentID() == right.getCurrentID();
}
Bullet & Bullet::operator=(Bullet other)
	{
		//*this = other; => JE le laisse pour les perles des bugs qui sont longs, chiants a d�buggers et non verbeux

		damage = other.damage;
		owner = other.owner;
		toDelete = other.toDelete;
		centerOnEnnemy = other.centerOnEnnemy;
		towardEnnemy = other.towardEnnemy;

		elapsed = other.elapsed;


		Body::operator=(other);

		myBodyDef.userData = this;
		if (b2body)
		{
			b2body->SetUserData(this);
		}

		return *this;
	}

void Bullet::preContact(Body * other)
{
	other->preContact(this);
}
void Bullet::preContact(Character* other)
{
	startCollision(other);
	other->startCollision(this);
}

void Bullet::preContact(Bullet * other)
{//do nothin'
}

//On s'en occupera quand les lapins auront des becs
//Edit: les li�vres ne comptent pas.
void Bullet::postContact(Body * other)
{
//	other->postContact(this);
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
	return std::make_unique<Bullet>(*world, textureActuelle,bodydef, myFixtureDef, damage, owner, 
		centerOnEnnemy, towardEnnemy,shape,elapsed);
}

