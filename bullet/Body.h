#pragma once
#include "stdafx.h"
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include <vector>
/// <summary>
/// Poss�de un corps physique 
/// </summary>
class Body
{
public:

	Body(b2World &world, sf::Texture* textureActuelle , b2BodyDef myBodyDef,b2FixtureDef fixtureDef, std::shared_ptr<b2Shape> shape):
		world(&world), textureActuelle(textureActuelle),myBodyDef(myBodyDef),myFixtureDef(fixtureDef),shape(shape){
		b2body = nullptr;
		//std::make_unique<b2Shape>(shape);
		
		sprite.setTexture(*textureActuelle);
		if (shape->m_type == b2Shape::e_circle)//on mets plutot au centre de la sprite
		{
			sprite.setOrigin(spriteWidth / 2, spriteHeight * 0.7);
		}
		else if(shape->m_type == b2Shape::e_polygon)
		{
			b2PolygonShape* rectShape = static_cast<b2PolygonShape*>(shape.get());
			spriteHeight = abs(rectShape->GetVertex(0).y*2);
			spriteWidth = abs(rectShape->GetVertex(0).x*2);
			sprite.setOrigin(-rectShape->GetVertex(0).x, -rectShape->GetVertex(0).y);
		}
		sprite.setTextureRect(sf::IntRect(currentstate*spriteWidth, 0, spriteWidth, spriteHeight));
		

		//on pr�pare le r�f�rencement a this
	};
	virtual void draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
		if (drawHitBox)
		{
			window.draw(hitbox);
		}
	}

	virtual void updateUserData() { myBodyDef.userData = this; }
	virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual void startCollision(Body* other);
	virtual void endCollision(Body* other);
	virtual std::unique_ptr<Body> clone() = 0;
	void updateVisuel();
	void createPhysical()
	{
		//myFixtureDef.isSensor = true;
	//	myBodyDef.userData = this;
		//myFixtureDef.userData = this;
		b2body=world->CreateBody(&myBodyDef);
		fixture=b2body->CreateFixture(&myFixtureDef);
		if (myFixtureDef.shape->GetType() == b2Shape::e_circle)
		{
			hitbox.setRadius(myFixtureDef.shape->m_radius);
			hitbox.setOrigin(sf::Vector2f(hitbox.getRadius(), hitbox.getRadius()));
			hitbox.setFillColor(sf::Color::Red);
		}
		else
		{
			drawHitBox = false;
		}
		b2body->SetUserData(this);
	};
	void setTextureActuelle(sf::Texture* texture) { textureActuelle = texture; };
	~Body()
	{
		//if (b2body != nullptr)
		//{
//			world->DestroyBody(b2body); //On d�truit le body dans le world
		//}
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