#pragma once
#include "Character.h"
#include <vector>
//Classe qui permet de charger en mémoire les pattern
class Pattern :
	public Character
{
private:
	std::vector<Bullet> bullets;
public:
	void createFromXml();//permet de charger les bullets en mémoire, mais n'instancie pas les objets physiques
	Pattern();
	~Pattern();
};

