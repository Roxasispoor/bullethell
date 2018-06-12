#include "stdafx.h"
#include "Character.h"

void Character::preContact(Body * other)
{
	other->preContact(this);
}

void Character::preContact(Bullet * bullet)
{
		startCollision(bullet);
		bullet->startCollision(this);
	
}

void Character::postContact(Body * other)
{
//	other->postContact(this);
}

void Character::startCollision(Bullet * other)
{
	if (other->getOwner() != this)
	{
		vieActuelle -= other->getDamage();
		if (vieActuelle <= 0)
		{
			onDeath();
		}
		
	}
}

/// <summary>
/// Updates the physics of the character et l'état de sa sprite Main loop
/// </summary>
void Character::updatePhysics(std::chrono::duration<double> elapsed)
{
	accumulated += elapsed;
	if (accumulated > timePassNext)
	{
		accumulated -= timePassNext;
		currentstate = (currentstate + 1) % numberState;
		sprite.setTextureRect(sf::IntRect(currentstate*spriteWidth, hauteurInSprite*spriteHeight, spriteWidth, spriteHeight));
	}
	//Depile toutes les commandes
	while (!commands.empty()) 
	{
		commands.front().execute();
		commands.pop_front();
	}
	for (auto &p : patterns)
	{
		p.updatePhysics();
	}
}
/// <summary>
/// Activate the pattern.
/// </summary>
void Character::shoot()
{

	 if (patterns.size() > 0 && !patterns[chosenPattern].getIsActivated() &&
		 patterns[chosenPattern].getTimer() < std::chrono::system_clock::now())
	{

		patterns[chosenPattern].setTimerNow();
		patterns[chosenPattern].activate(false);
	}
}
/// <summary>
/// Brights this instance. TODO
/// </summary>
void Character::bright()
{
}
/// <summary>
/// Trigerred on death.
/// </summary>
void Character::onDeath()
{
	std::cout << "FIN DU JEU";
	/*sf::Font font;

	// Chargement à partir d'un fichier sur le disque
	if (!font.loadFromFile("arial.ttf"))
	{
		// Erreur...
	}
	sf::Text text;
	text.setFont(font); // font is a sf::Font

						// set the string to display
	text.setString("Fin du jeu");

	// set the character size
	text.setCharacterSize(24);
	*/
	//exit;
	
}
/// <summary>
/// Moves this instance.
/// </summary>
void Character::move()
{
	
	toGo.Normalize();
	b2body->SetLinearVelocity(b2Vec2(toGo.x*speedFrame*multiplierMove , toGo.y*speedFrame*multiplierMove));
	
}
/// <summary>
/// Draws the specified object on window and call recursively on patterns
/// </summary>
/// <param name="window">The window.</param>
void Character::draw(sf::RenderWindow & window)
{
	Body::draw(window);
	for (auto &x : patterns)
	{
		
		x.draw(window);
	}
}

