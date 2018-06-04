#pragma once
#include "stdafx.h"
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include <vector>
/// <summary>
/// Possède un corps physique 
/// </summary>
class Body
{
public:

	Body(b2World &world, sf::Texture* textureActuelle , b2BodyDef myBodyDef,b2CircleShape shape):
		world(&world), textureActuelle(textureActuelle),myBodyDef(myBodyDef),shape(shape){
		//std::make_unique<b2Shape>(shape);
		myBodyDef.userData = this;
		myFixtureDef.shape = &shape;
		//on prépare le référencement a this
	};
	/*
	Body(b2World &world, sf::Texture* textureActuelle, b2BodyDef myBodyDef, b2PolygonShape shape) :
		world(&world), textureActuelle(textureActuelle), myBodyDef(myBodyDef) {
		std::make_unique<b2Shape>(shape);
		myBodyDef.userData = this;
		myFixtureDef.shape = &shape;//on prépare le référencement a this
	};
	Body(b2World &world, sf::Texture* textureActuelle, b2BodyDef myBodyDef, b2EdgeShape shape) :
		world(&world), textureActuelle(textureActuelle), myBodyDef(myBodyDef) {
		std::make_unique<b2Shape>(shape);
		myBodyDef.userData = this; //on prépare le référencement a this
		myFixtureDef.shape = &shape;};
		*/
	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual void startCollision(Body* other);
	virtual void endCollision(Body* other);
	virtual std::unique_ptr<Body> clone() = 0;
	void createPhysical()
	{
		b2body=world->CreateBody(&myBodyDef);
		fixture=b2body->CreateFixture(&myFixtureDef);

	};
	void setTextureActuelle(sf::Texture* texture) { textureActuelle = texture; };
	~Body()
	{
		world->DestroyBody(b2body); //On détruit le body dans le world
	}
	
private: 
	
	
protected:

	b2CircleShape shape;
	b2Fixture* fixture;
	sf::Texture* textureActuelle;
	b2BodyDef myBodyDef;
	b2FixtureDef myFixtureDef;

	b2Body * b2body;
	b2World *world;
	sf::Sprite sprite;

};