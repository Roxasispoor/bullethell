#include "stdafx.h"
#include "Body.h"


void Body::preContact(Body * other)
{
	other->preContact(this);
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

void Body::updateVisuel()
{

	sprite.setPosition(b2body->GetPosition().x, b2body->GetPosition().y);
	hitbox.setPosition(b2body->GetPosition().x, b2body->GetPosition().y);
}

