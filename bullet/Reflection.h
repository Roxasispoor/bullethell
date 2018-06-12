#pragma once
#include "Box2D/Box2D.h"
/// <summary>
/// Classe mère permettant de modifier des bodydef et de les répéter
/// </summary>
class Reflection
{
public:
	Reflection();
	Reflection(bool applyOnForce) :applyOnForce(applyOnForce) {};
	Reflection(bool applyOnForce,bool centeredOnEnnemy, bool isAbsolute,b2Vec2 pointDepart) :
		applyOnForce(applyOnForce),centeredOnEnnemy(centeredOnEnnemy),isAbsolute(isAbsolute), decalage(pointDepart){};
//	virtual std::shared_ptr<Reflection> cloneXML(pugi::xml_node node);
	virtual ~Reflection();
	virtual void applyReflection(b2BodyDef& body);
	int getnumberCopies() { return numberCopies; };
	bool getIsAbsolute() {	return isAbsolute;};
	bool getCenteredOnEnnemy() {	return centeredOnEnnemy;};
	void setPointDepart(b2Vec2 pos) { centre = pos; };
protected:
	b2Vec2 centre;
	b2Vec2 decalage;
	bool isAbsolute = false;
	bool applyOnForce = true;
	bool centeredOnEnnemy = false;
	int numberCopies = 1;
};

