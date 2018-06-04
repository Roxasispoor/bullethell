#include "stdafx.h"
#include "AxialSymmetry.h"

void AxialSymmetry::applyReflection(b2BodyDef & body)
{
	b2Vec2 normal=b2Cross((body.position-pointDepart).Length(), directeur);
	body.position -= 2 * normal;//On soustrait 2* vecteur

	//On calcule l'angle entre la symétrie et un pigeon 
	body.angle-=2*acos(b2Dot(b2Vec2(1,0),directeur)); //marche par pitié

	if (applyOnForce)
	{
		b2Vec2 normalForce = b2Cross(body.linearVelocity.Length(), directeur);
		body.linearVelocity -= 2 * normalForce;
	}
}
