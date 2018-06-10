#pragma once
#include "Box2D/Box2D.h"
class Reflection
{
public:
	Reflection();
	Reflection(bool applyOnForce) :applyOnForce(applyOnForce) {};
	Reflection(bool applyOnForce,bool centeredOnEnnemy, bool isAbsolute,b2Vec2 pointDepart) :
		applyOnForce(applyOnForce),centeredOnEnnemy(centeredOnEnnemy),isAbsolute(isAbsolute) {};
//	virtual std::shared_ptr<Reflection> cloneXML(pugi::xml_node node);
	virtual ~Reflection();
	virtual void applyReflection(b2BodyDef& body);
	int getnumberCopies() { return numberCopies; };
	bool getIsAbsolute() {	return isAbsolute;};
	bool getCenteredOnEnnemy() {	return centeredOnEnnemy;};

protected:
	b2Vec2 pointDepart;
	bool isAbsolute = false;
	bool applyOnForce = true;
	bool centeredOnEnnemy = false;
	int numberCopies = 1;
};

