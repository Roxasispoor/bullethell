#pragma once
#include "Box2D/Box2D.h"
class Reflection
{
public:
	Reflection();
	Reflection(bool applyOnForce) :applyOnForce(applyOnForce) {};
	Reflection(bool applyOnForce,bool centeredOnEnnemy) :applyOnForce(applyOnForce),centeredOnEnnemy(centeredOnEnnemy) {};
//	virtual std::shared_ptr<Reflection> cloneXML(pugi::xml_node node);
	virtual ~Reflection();
	virtual void applyReflection(b2BodyDef& body);
	int& getnumberCopies() { return numberCopies; };
protected:
	bool applyOnForce = true;
	bool centeredOnEnnemy = false;
	int numberCopies = 1;
};

