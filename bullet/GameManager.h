#pragma once
#include "Body.h"
#include "Character.h"
#include <vector>
#include "Ennemy.h"
#include "Player.h"
#include <chrono>
class GameManager
{

public:
	GameManager() :gravity(0,0),world(gravity) {};
	~GameManager();
	void mainLoop();
	void render(double timeOnNextFrame);
	

private:
	b2World world;
	Player joueur;
	std::vector<Ennemy> ennemisPossibles;
	std::vector<Ennemy> ennemisEnVie;
	b2Vec2 gravity; //nogravity
//	bool doSleep = true;
};
	

