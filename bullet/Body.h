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
/// <summary>
/// Classe de base de toute objet qui possède une réalité physique
/// </summary>
class Body
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Body"/> class. N'a pas encore d'existence physique
	/// </summary>
	/// <param name="world">The world.</param>
	/// <param name="textureActuelle">The texture actuelle.</param>
	/// <param name="myBodyDef">My body definition.</param>
	/// <param name="fixtureDef">The fixture definition.</param>
	/// <param name="shape">The shape.</param>
	Body(b2World &world, sf::Texture* textureActuelle, b2BodyDef myBodyDef, b2FixtureDef fixtureDef, std::shared_ptr<b2Shape> shape) :
		world(&world), textureActuelle(textureActuelle),myBodyDef(myBodyDef),myFixtureDef(fixtureDef),shape(shape),currentID(ID++){
		b2body = nullptr;
		myFixtureDef.isSensor = true;
		sprite.setTexture(*textureActuelle);
	
		if (shape->m_type == b2Shape::e_circle)//on mets plutot au centre de la sprite
		{
			sprite.setOrigin(spriteWidth / 2, spriteHeight /2);
		}
		else if(shape->m_type == b2Shape::e_polygon)
		{
			b2PolygonShape* rectShape = static_cast<b2PolygonShape*>(shape.get());
			spriteHeight = abs(rectShape->GetVertex(0).y*2);
			spriteWidth = abs(rectShape->GetVertex(0).x*2);
			sprite.setOrigin(-rectShape->GetVertex(0).x, -rectShape->GetVertex(0).y);
			sprite.setScale(spriteWidth / float(textureActuelle->getSize().x), spriteHeight / float(textureActuelle->getSize().y));
		//	sprite.setTextureRect(sf::IntRect(currentstate*spriteWidth, 0, spriteWidth, spriteHeight));
		}
		
		


	};	
	/// <summary>
	/// Draws the specified object on window.
	/// </summary>
	/// <param name="window">The window.</param>
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
	
	/// <summary>
	/// Operator=s the specified other. Necessary for push backs due to userdata
	/// </summary>
	/// <param name="other">The other.</param>
	/// <returns></returns>
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
	/// <summary>
	/// Determines whether this instance is valid. Maraboutage.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is valid; otherwise, <c>false</c>.
	/// </returns>
	bool isValid() { return textureActuelle != nullptr; }
	
	/// <summary>
	/// Operator=s the specified other. Rule of 5
	/// </summary>
	/// <param name="other">The other.</param>
	/// <returns></returns>
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
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Body"/> class.
	/// </summary>
	/// <param name="other">The other.</param>
	Body(const Body& other);


	/// <summary>
	/// Creates the physical representation of the body, both in box2D and sprites wise
	/// </summary>
	void createPhysical();

	void setTextureActuelle(sf::Texture* texture) { textureActuelle = texture; };
	sf::Sprite& getSprite() { return sprite; };
	b2Body* getB2Body() { return b2body; }
	b2BodyDef& getBodyDef() {
		return myBodyDef;
	};
	std::shared_ptr<b2Shape>& getShape() { return shape ; };
	void setShape(std::shared_ptr<b2Shape> shapey) { shape = shapey; };
		b2World* getWorld() { return world; };
		const int  getCurrentID() const {
		return currentID;
	};
	~Body()
	{
	};
	
protected:

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
