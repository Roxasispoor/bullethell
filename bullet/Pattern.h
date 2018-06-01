#pragma once
#include "Character.h"
#include "AbstractSpawner.h"
#include "Bullet.h"
#include <vector>
class Bullet;
//Classe qui permet de charger en mémoire les pattern / les tirer
class Pattern:public AbstractSpawner
{
private:
	std::vector<Bullet> bullets;

public:
	void createFromXml();//permet de charger les bullets en mémoire, mais n'instancie pas les objets physiques
	Pattern(b2World world) :AbstractSpawner(world) {};
	~Pattern();
	void createShoot();
	void repeat();
};

