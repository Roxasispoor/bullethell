#pragma once
#include "Body.h"
#include "Character.h"
#include <vector>
#include "Ennemy.h"
class GameManager
{

public:
	GameManager() :gravity(0,0),world(gravity) {};
	~GameManager();
	

private:
	b2World world;
	Character hero;
	std::vector<Ennemy> ennemisPossibles;
	std::vector<Ennemy> ennemisEnVie;
	b2Vec2 gravity; //nogravity
//	bool doSleep = true;
};
	

