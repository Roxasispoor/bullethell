#pragma once
#include "Reflection.h"
/// <summary>
/// Classe permettant de faire une symétrie axiale des bullets, selon un vecteur directeur.
/// Ne marche dans l'etat actuel
/// </summary>
/// <seealso cref="Reflection" />
class AxialSymmetry :
	public Reflection
{
private:

	b2Vec2 directeur;
	
public:
	virtual void applyReflection(b2BodyDef& body);
		AxialSymmetry(bool applyOnForce,bool centeredOnEnnemy, b2Vec2 pointDepart, b2Vec2 directeur,bool isAbsolute):
		Reflection(applyOnForce,centeredOnEnnemy,isAbsolute,pointDepart), directeur(directeur) {};

	
};
