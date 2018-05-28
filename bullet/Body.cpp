#include "stdafx.h"
#include "Body.h"


Body::~Body()
{
}

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

