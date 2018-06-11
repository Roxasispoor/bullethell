#include "stdafx.h"
#include "RepeatRotation.h"




RotationOnce::~RotationOnce()
{
}

void RotationOnce::applyReflection(b2BodyDef & body)
{
	
	body.angle += angularDiff;
	body.position -= centre;
	
	
	float length = body.position.Length();
	body.position.x = length * cos(body.angle)+ centre.x;
	body.position.y = length * sin(body.angle)+ centre.y;

	float normeForce = body.linearVelocity.Length();
	body.linearVelocity.x=normeForce* cos(body.angle);
	body.linearVelocity.y=normeForce* sin(body.angle);

	}
