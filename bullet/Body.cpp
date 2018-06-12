#include "stdafx.h"
#include "Body.h"
#include "Bullet.h"
int Body::ID = 0;

bool operator==(const Body & left, const Body & right)
{

	return left.getCurrentID() == right.getCurrentID();
}

void Body::preContact(Body * other)
{
	//other->preContact(this);
}

void Body::preContact(Character * other)
{
}

void Body::preCollision(Player * other)
{
}

void Body::preContact(Bullet * other)
{
}

void Body::postContact(Body * other)
{
	other->postContact(this);
}

void Body::startCollision(Body * other)
{ //pas d'interaction particulière
}

void Body::endCollision(Body * other)
{
}
/// <summary>
/// Updates the visual. met en accord la position box2d et sfml
/// </summary>
void Body::updateVisuel()
{

	sprite.setPosition(b2body->GetPosition().x, b2body->GetPosition().y);
	sprite.setRotation(b2body->GetAngle() * 180 / b2_pi);
	hitbox.setPosition(b2body->GetPosition().x, b2body->GetPosition().y);
}
/// <summary>
/// Initializes a new instance of the <see cref="Body"/> class.
/// </summary>
/// <param name="other">The other.</param>
Body::Body(const Body & other) :shape(other.shape), fixture(other.fixture),
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
}
/// <summary>
/// Creates the physical aspect in box2d and sprites
/// </summary>
void Body::createPhysical()

{
	//SHAPE IS CLONED BY BOX2d
	b2body = world->CreateBody(&myBodyDef);
	fixture = b2body->CreateFixture(&myFixtureDef);
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


