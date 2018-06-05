#include "stdafx.h"
#include "monMain.h"
#include "Box2D/Box2D.h"
#include "GameManager.h"
int monMain()
{
	GameManager gameManager;
	gameManager.mainLoop();
	return 0;
}