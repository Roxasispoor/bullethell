#include "stdafx.h"
#include "GameManager.h"
#define FPS 60.f



GameManager::~GameManager()
{
}

void GameManager::mainLoop()
{
	auto previous = std::chrono::system_clock::now();
	std::chrono::duration<double> durationFrame(1 / FPS);
	std::chrono::duration<double> lag;
	const int maxSteps = 5;
	while (true)
	{
		auto current = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = current - previous;
		//Si on a trop de frame de retard on
		//elapsed = std::min(elapsed, maxSteps * durationFrame);
		previous = current;
		lag += elapsed;
		for (auto &joueur : joueurs)
		{
			joueur.input();
		}
		while (lag >= durationFrame);
		{
			//const int nStepsClamped = std::min(nSteps, MAX_STEPS);
				//update world
			for (auto &joueur : joueurs)
			{
				joueur.updatePhysics();
				world.Step(1 / FPS, 8, 3);
				lag -= durationFrame;
			}
		}

		render(lag/durationFrame);
	}
}
