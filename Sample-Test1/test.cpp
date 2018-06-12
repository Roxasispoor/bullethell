#include "pch.h"
#include "../bullet/GameManager.h"
#include "../bullet/Body.h"
class Body;
TEST(TestCaseName, TestName) {
	GameManager gameManager;
	EXPECT_GT(gameManager.getEnnemisPossibles().size(), 0);
	EXPECT_GT(gameManager.getPatternsPossibles().size(),0);
	EXPECT_GT(gameManager.getTextureMap().size(),0);
	EXPECT_GT(gameManager.getJoueurs().size(),0);
	EXPECT_GT(gameManager.getEnnemisPossibles().size(),0);
	gameManager.getEnnemisEnVie().push_back(gameManager.getEnnemisPossibles()[0]);//*(static_cast<Ennemy*>(ennemisPossibles[0].clone().get())));
	EXPECT_GT(gameManager.getEnnemisEnVie().size(), 0);
	gameManager.getEnnemisEnVie()[0].createPhysical();
	EXPECT_NE(gameManager.getEnnemisEnVie()[0].getB2Body(), nullptr);

	EXPECT_NE(gameManager.getEnnemisEnVie()[0].getBodyDef().position.x,0);
	EXPECT_NE(gameManager.getEnnemisEnVie()[0].getBodyDef().position.y,0);
	EXPECT_NE(gameManager.getEnnemisEnVie()[0].getBodyDef().userData,nullptr);
	gameManager.getEnnemisEnVie()[0].getPatterns()[0].createPhysical();
	
}