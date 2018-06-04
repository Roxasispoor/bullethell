#pragma once
#include "Box2D/Box2D.h"
class Reflection
{
public:
	Reflection();
	Reflection(bool applyOnForce) :applyOnForce(applyOnForce) {};
	virtual ~Reflection();
	virtual void applyReflection(b2BodyDef& body);
protected:
	bool applyOnForce = true;
};

