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

