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

	Body(b2World &world, sf::Texture* textureActuelle , b2BodyDef myBodyDef,b2FixtureDef fixtureDef):
		world(&world), textureActuelle(textureActuelle),myBodyDef(myBodyDef),myFixtureDef(fixtureDef){
		b2body = nullptr;
		//std::make_unique<b2Shape>(shape);
		myBodyDef.userData = this;
		sprite.setTexture(*textureActuelle);
		sprite.setOrigin(spriteWidth / 2, spriteHeight * 0.7);
		sprite.setTextureRect(sf::IntRect(currentstate*spriteWidth, 0, spriteWidth, spriteHeight));
		

		//on prépare le référencement a this
	};
	void draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
		if (drawHitBox)
		{
			window.draw(hitbox);
		}
	}

	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual void startCollision(Body* other);
	virtual void endCollision(Body* other);
	virtual std::unique_ptr<Body> clone() = 0;
	void updateVisuel();
	void createPhysical()
	{
		b2body=world->CreateBody(&myBodyDef);
		fixture=b2body->CreateFixture(&myFixtureDef);
		hitbox.setRadius(fixture->GetShape()->m_radius);
		hitbox.setOrigin(sf::Vector2f(hitbox.getRadius(), hitbox.getRadius()));
		hitbox.setFillColor(sf::Color::Red);
	};
	void setTextureActuelle(sf::Texture* texture) { textureActuelle = texture; };
	~Body()
	{
		if (b2body != nullptr)
		{
			world->DestroyBody(b2body); //On détruit le body dans le world
		}
	}
	sf::Sprite& getSprite() { return sprite; };
	b2Body* getB2Body() { return b2body; }
	b2BodyDef& getBodyDef() {
		return myBodyDef;
	};
	std::shared_ptr<b2Shape>& getShape() { return shape ; };
	void setShape(std::shared_ptr<b2Shape> shapey) { shape = shapey; };
	//void setShape( shapey) { shape=shapey ; };
	//void setShape(b2PolygonShape& shapey) { shape=shapey ; };
	
	//b2Body* getB2Body() { return b2body; }
	//b2World* getWorld() { return world; };
	//sf::Texture* getTexture() { return world; };

	
	
	
protected:

	//b2CircleShape shape;
	std::shared_ptr<b2Shape> shape;
	b2Fixture* fixture;
	sf::Texture* textureActuelle;
	b2BodyDef myBodyDef;
	b2FixtureDef myFixtureDef;
	b2Body * b2body;
	b2World *world;
	sf::CircleShape hitbox;
	bool drawHitBox = true;
	sf::Vector2i screenWidth;
	sf::Sprite sprite;
	int spriteWidth = 48;
	int spriteHeight = 64;
	int currentstate = 1;
	int hauteurInSprite=0;
};