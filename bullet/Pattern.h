#pragma once
#include "Character.h"
#include <vector>
//Classe qui permet de charger en m�moire les pattern
class Pattern :
	public Character
{
private:
	std::vector<Bullet> bullets;
public:
	void createFromXml();//permet de charger les bullets en m�moire, mais n'instancie pas les objets physiques
	Pattern();
	~Pattern();
};

