#pragma once
#include "Bullet.h"
#include "Pattern.h"
class Character:Body
{
public:
	Character();
	virtual ~Character();
	virtual void shoot() = 0;
	virtual void onDeath();
	std::vector<Bullet*>& getCurrentBullets() {
		return currentBullets;
	}
	std::vector<Bullet*>& getToDelete() {
		return toDelete;
	}

private:
	std::vector<Pattern> patterns;
	float vieMax;
	float vieActuelle;
	std::vector<Bullet*> currentBullets;
	std::vector<Bullet*> toDelete;

};

