#pragma once
#include "Reflection.h"
class RotationOnce :
	public Reflection
{
	b2Vec2 pointcentral;
	float angularDiff;
public:
	RotationOnce(bool applyOnForce,bool centeredOnEnnemy,int numberRepeat, b2Vec2 pointcentral,float angularDiff)
	:Reflection(applyOnForce, centeredOnEnnemy),pointcentral(pointcentral),angularDiff(angularDiff)
	{
		numberCopies = numberRepeat;
	};
	~RotationOnce();

	virtual void applyReflection(b2BodyDef& body);


};

