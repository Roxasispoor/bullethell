#include "stdafx.h"
#include "RepeatRotation.h"




RotationOnce::~RotationOnce()
{
}

void RotationOnce::applyReflection(b2BodyDef & body)
{
	body.angle += angularDiff;
	float length = (body.position - pointcentral).Length();
	body.position.x = length * cos(body.angle);
	body.position.y = length * sin(body.angle);
	float normeForce = body.linearVelocity.Length();
	body.linearVelocity.x=normeForce* cos(body.angle);
	body.linearVelocity.x=normeForce* sin(body.angle);
}
