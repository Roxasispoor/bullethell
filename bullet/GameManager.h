#pragma once
#include "Body.h"
#include "Character.h"
#include <vector>
#include "Ennemy.h"
#include "Player.h"
#include <chrono>
#include "MyContactListenner.h"
#include "const.h"


class GameManager
{

	
public:
	GameManager() :gravity(0, 0), world(gravity),textureMap(),
		window(sf::VideoMode(1920, 1080), "Bullet heaven", sf::Style::Fullscreen) {

		//world.SetDebugDraw(
			//world.SetDebugDraw();
		for (auto x : aliasFichierNames) //On remplit les textures et on les mets a jour
		{

			textureMap[x.second];
			if (!textureMap[x.second].loadFromFile(x.first))
			{
				std::cout << "erreur de chargement de " << x.first;
			}
		}
		
		b2FixtureDef fixturePlayer;
		 b2CircleShape shapePlayer;
		 b2BodyDef bodyDef;
		 bodyDef.type = b2_dynamicBody; //this will be a dynamic body
		 shapePlayer.m_radius = 5;
		 fixturePlayer.shape = &shapePlayer; //sera copiée, np
		  joueurs.push_back(Player (world, &textureMap["joueur"], bodyDef, fixturePlayer));
		  joueurs[0].createPhysical();
		
		//joueurs[0].setTextureActuelle(&textureMap["joueur"]);
	};//on remplira la texture du joueur juste après les avoir load
	~GameManager();
	void mainLoop();
	void render(double timeOnNextFrame);


private:
	//const std::pair<std::string, std::string>aliasFichiers = { ["blah","blah"] };
	
	std::map<std::string, std::string> aliasFichierNames = { {"../joueur.png","joueur"} };
	b2World world;
	
	//Player joueur;
	std::map<std::string, sf::Texture> textureMap;
	std::vector<Player> joueurs;
	std::vector<Ennemy> ennemisPossibles;
	std::vector<Ennemy> ennemisEnVie;
	b2Vec2 gravity; //nogravity
	MyContactListener listenner;
	sf::RenderWindow window;

	bool doSleep = true;
};
	

