#include "stdafx.h"
#include "GameManager.h"




GameManager::~GameManager()
{
}

void GameManager::mainLoop()
{
	auto previous = std::chrono::system_clock::now();
	std::chrono::duration<double> durationFrame(1 / FPS);
	std::chrono::duration<double> lag;
	const int maxSteps = 5;
	while (window.isOpen())
	{
		auto current = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = current - previous;
		//Si on a trop de frame de retard on
		//elapsed = std::min(elapsed, maxSteps * durationFrame);
		previous = current;
		lag += elapsed;
		
		while (lag >= durationFrame);
		{

			//const int nStepsClamped = std::min(nSteps, MAX_STEPS);
				//update world
			for (auto &joueur : joueurs)
			{
				joueur.input();
				joueur.updatePhysics();
				world.Step(1 / FPS, 8, 3);
				b2Vec2 newpos = joueur.getB2Body()->GetPosition();
				joueur.getSprite().setPosition(newpos.x, newpos.y);

				lag -= durationFrame;
			}
		}
		window.clear(sf::Color::Black);
		render(lag/durationFrame);
	}
}

void GameManager::render(double timeOnNextFrame)
{
	world.DrawDebugData();
	for (auto &x : joueurs)
	{
		window.draw(x.getSprite());
		
	}
	window.display();

}
