#pragma once
#include "Reflection.h"
/// <summary>
/// Permet de décaler les bodydef d'un angle angleDiff
/// </summary>
/// <seealso cref="Reflection" />
class RotationOnce :
	public Reflection
{
	
	float angularDiff;
public:
	RotationOnce(bool applyOnForce,bool centeredOnEnnemy,int numberRepeat, b2Vec2 pointDepart,float angularDiff, bool isAbsolute)
	:Reflection(applyOnForce, centeredOnEnnemy,isAbsolute,pointDepart),angularDiff(angularDiff)
	{
		numberCopies = numberRepeat;
	};
	~RotationOnce();

	virtual void applyReflection(b2BodyDef& body);


};

