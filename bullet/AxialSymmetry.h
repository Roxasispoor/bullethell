#pragma once
#include "Reflection.h"
class AxialSymmetry :
	public Reflection
{
private:
	b2Vec2 pointDepart;
	b2Vec2 directeur;
	
public:
	virtual void applyReflection(b2BodyDef& body);
	AxialSymmetry(b2Vec2 pointDepart,b2Vec2 directeur):pointDepart(pointDepart),directeur(directeur) {};
//	AxialSymmetry(bool applyOnForce, b2Vec2 pointDepart, b2Vec2 directeur) :pointDepart(pointDepart), directeur(directeur) {};
	AxialSymmetry(bool applyOnForce, b2Vec2 pointDepart, b2Vec2 directeur):Reflection(applyOnForce),pointDepart(pointDepart), directeur(directeur) {};

	~AxialSymmetry();

};

//STIER:Simulation and Training Interface for Entertainment of Riders