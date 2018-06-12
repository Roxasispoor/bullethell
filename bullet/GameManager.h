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
	GameManager(); 
	void mainLoop();
	void render(double timeOnNextFrame);
	void createPatternsFromXml(std::string patternsFile);
	
	b2World& getWorld() { return world; };

	std::vector<Pattern>& getPatternsPossibles() { return patternsPossibles; };
	std::map<std::string, sf::Texture>& getTextureMap(){ return textureMap; };
	std::vector<Player>& getJoueurs() { return joueurs; };
	std::vector<Ennemy>& getEnnemisPossibles(){return ennemisPossibles; };
	std::vector<Ennemy>& getEnnemisEnVie() { return ennemisEnVie; }; 
	MyContactListener& getListenner() { return listenner; };


private:
	
	std::map<std::string, std::string> aliasFichierNames = { {"../joueur.png","joueur"},{"../bullets.png","bullet"},{ "../laser.png","laser"},{"../ghostmaiden.png","ghostmaiden"} };
	b2World world;

	std::vector<Pattern> patternsPossibles;
	std::map<std::string, sf::Texture> textureMap;
	std::vector<Player> joueurs;
	std::vector<Ennemy> ennemisPossibles;
	std::vector<Ennemy> ennemisEnVie;
	b2Vec2 gravity; //nogravity
	MyContactListener listenner;
	sf::RenderWindow window;

	bool doSleep = true;
};
	