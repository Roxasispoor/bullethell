#include "stdafx.h"
#include "Pattern.h"


void Pattern::deleteAtEndStep()
{
	currentBullets.erase(
		std::remove_if(currentBullets.begin(), currentBullets.end(),
			[](const std::unique_ptr<Bullet> & o) { return o->getToDelete(); }),
		currentBullets.end());
}

//... Ah la bonne non covenance sur les pointeurs intelligents 
void Pattern::createShoot()
{
	auto tempsactuel = std::chrono::high_resolution_clock::now(); //On évite de rester a jamais dans la boucle si elle prend trop de temps
	//for (auto &bullet : bullets)
	while(timer<tempsactuel)
	{

		std::unique_ptr<Bullet>
		derivedPointer(static_cast<Bullet*>(bullets[bulletIndice].clone().release()));
		derivedPointer->createPhysical();//On rend le bullet physique
		//+= derivedPointer->getElapsed();
		timer+= derivedPointer->getElapsed() ;
		currentBullets.push_back(std::move(derivedPointer)); //On move
		//on ajoute le temps et on update indice
		bulletIndice++;
	}
		//on verra les reflexions plus tard
//reflected = (((normal dot vecteur) * normal) * 2) + vecteur
	/*	b2Cross(
	for(x:
	}*/
	

}

void Pattern::updatePhysics()
{
	//Si on est activé on shoot ce qu'il faut
	if (isActivated)
	{
		createShoot();
	}
}
