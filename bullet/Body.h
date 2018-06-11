#pragma once
#include "stdafx.h"
#include "Box2D/Box2D.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
/// <summary>
/// Possède un corps physique 
/// </summary>
class Character;
class Bullet;
class Player;
class Body
{
public:

	Body(b2World &world, sf::Texture* textureActuelle , b2BodyDef myBodyDef,b2FixtureDef fixtureDef, std::shared_ptr<b2Shape> shape):
		world(&world), textureActuelle(textureActuelle),myBodyDef(myBodyDef),myFixtureDef(fixtureDef),shape(shape),currentID(ID++){
		b2body = nullptr;
		//std::make_unique<b2Shape>(shape);
		
		myFixtureDef.isSensor = true;
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
		

		//on prépare le référencement a this
	};
	virtual void draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
		if (drawHitBox)
		{
			window.draw(hitbox);
		}
	}

		virtual void preContact(Body* other);// Implementation patron multi dispatcher celui-ci 
	virtual void preContact(Character* other);
	virtual void preCollision(Player * other);
	virtual void preContact(Bullet* other);
	virtual void postContact(Body* other);// Implementation patron multi dispatcher
	virtual void startCollision(Body* other);
	virtual void endCollision(Body* other);
	virtual std::unique_ptr<Body> clone() = 0;
	void updateVisuel();
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Body"/> class.
	/// </summary>
	/// <param name="other">The other.</param>
	Body(Body && other) :
		shape(std::move(other.shape)), fixture(std::move(other.fixture)),
		textureActuelle(std::move(other.textureActuelle)), myBodyDef(std::move(other.myBodyDef)),
		myFixtureDef(std::move(other.myFixtureDef)), b2body(std::move(other.b2body)), world(std::move(other.world)),
		hitbox(std::move(other.hitbox)), drawHitBox(std::move(other.drawHitBox)), screenWidth(std::move(other.screenWidth)),
		sprite(std::move(other.sprite)), spriteWidth(std::move(other.spriteWidth)), spriteHeight(std::move(other.spriteHeight)),
		currentstate(std::move(other.currentstate)), hauteurInSprite(std::move(other.hauteurInSprite)),currentID(std::move(other.currentID))
	{
		myBodyDef.userData = this;
		if (b2body)
		{
			b2body->SetUserData(this);
		}
	};

	
	Body& operator=(Body&& other)
	{
	
		if (this != &other)
		{
			*this = std::move(other);
			myBodyDef.userData = this;
			if (b2body)
			{
				b2body->SetUserData(this);
			}

		}
		return *this;
	}

	bool isValid() { return textureActuelle != nullptr; }
//	Body& operator=(Bullet& other);

	Body& operator=(Body& other)
	{
		shape = other.shape;
		fixture = other.fixture;
		textureActuelle = other.textureActuelle;
		myBodyDef = other.myBodyDef;
		myFixtureDef = other.myFixtureDef;
		b2body = other.b2body;
		world = other.world;
		hitbox=other.hitbox;
		drawHitBox = other.drawHitBox;
		screenWidth = other.screenWidth;
		sprite=other.sprite;
		spriteWidth = other.spriteWidth;
		spriteHeight = other.spriteHeight;
		currentstate = other.currentstate;
		hauteurInSprite = other.hauteurInSprite;

		myBodyDef.userData = this;
		if (b2body)
		{
			b2body->SetUserData(this);
		}
		return *this;
	};


	Body(const Body& other):shape(other.shape), fixture(other.fixture),
		textureActuelle(other.textureActuelle), myBodyDef(other.myBodyDef),
		myFixtureDef(other.myFixtureDef), b2body(other.b2body), world(other.world),
		hitbox(other.hitbox), drawHitBox(other.drawHitBox), screenWidth(other.screenWidth),
		sprite(other.sprite), spriteWidth(other.spriteWidth), spriteHeight(other.spriteHeight),
		currentstate(other.currentstate), hauteurInSprite(other.hauteurInSprite)
	{
		currentID = ID++;
		myBodyDef.userData = this;
		if (b2body)
		{
			b2body->SetUserData(this);
		}
	};



	void createPhysical()
	{
		//myFixtureDef.isSensor = true;
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
	b2World* getWorld() { return world; };
	//sf::Texture* getTexture() { return world; };
	const int  getCurrentID() const {
		return currentID;
	};
	~Body()
	{
	};
	
protected:

	//b2CircleShape shape;
	std::shared_ptr<b2Shape> shape;
	b2Fixture* fixture=nullptr;
	sf::Texture* textureActuelle;
	b2BodyDef myBodyDef;
	b2FixtureDef myFixtureDef;
	b2Body * b2body=nullptr;
	b2World *world;
	sf::CircleShape hitbox;
	bool drawHitBox = true;
	sf::Vector2i screenWidth;
	sf::Sprite sprite;
	int spriteWidth = 48;
	int spriteHeight = 64;
	int currentstate = 1;
	int hauteurInSprite=0;
	static int ID;
	int currentID;
};
