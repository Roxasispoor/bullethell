#include "stdafx.h"
#include "Body.h"
#include "Bullet.h"
int Body::ID = 0;

bool operator==(const Body & left, const Body & right)
{

	return left.getCurrentID() == right.getCurrentID();
}

void Body::preContact(Body * other)
{
	other->preContact(this);
}

void Body::preContact(Character * other)
{
}

void Body::preContact(Bullet * other)
{
}

void Body::postContact(Body * other)
{
	other->postContact(this);
}

void Body::startCollision(Body * other)
{ //pas d'interaction particulière
}

void Body::endCollision(Body * other)
{
}
/// <summary>
/// Updates the visual. met en accord la position box2d et sfml
/// </summary>
void Body::updateVisuel()
{

	sprite.setPosition(b2body->GetPosition().x, b2body->GetPosition().y);
	hitbox.setPosition(b2body->GetPosition().x, b2body->GetPosition().y);
}

