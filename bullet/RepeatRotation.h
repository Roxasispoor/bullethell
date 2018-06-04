#pragma once
#include "Reflection.h"
class RotationOnce :
	public Reflection
{
	b2Vec2 pointcentral;
	float angularDiff;
public:
	RotationOnce();
	~RotationOnce();
	virtual void applyReflection(b2BodyDef& body);

};

