#pragma once
#include "Body.h"
#include "Character.h"
#include <vector>
#include "Ennemy.h"
#include "Player.h"
#include <chrono>
#include "MyContactListenner.h"

class GameManager
{

public:
	GameManager() :gravity(0, 0), world(gravity),textureMap(),joueur(world,nullptr,b2BodyDef(),b2CircleShape()) {
		for (auto x : aliasFichierNames) //On remplit les textures et on les mets a jour
		{
			textureMap[x.second];
			if (!textureMap[x.second].loadFromFile(x.first))
			{
				std::cout << "erreur de chargement de " << x.first;
			}
		}
		joueur.setTextureActuelle(&textureMap["joueur"]);
	};//on remplira la texture du joueur juste après les avoir load
	~GameManager();
	void mainLoop();
	void render(double timeOnNextFrame);


private:
	//const std::pair<std::string, std::string>aliasFichiers = { ["blah","blah"] };
	std::map<std::string, std::string> aliasFichierNames = { {"joueur.png","joueur"} };
	b2World world;
	Player joueur;
	std::map<std::string, sf::Texture> textureMap;
	std::vector<Ennemy> ennemisPossibles;
	std::vector<Ennemy> ennemisEnVie;
	b2Vec2 gravity; //nogravity
	MyContactListener listenner;
//	bool doSleep = true;
};
	

