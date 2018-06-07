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
		sf::Event event;
		while (window.pollEvent(event))
		{
			// fermeture de la fen�tre lorsque l'utilisateur le souhaite
			if (event.type == sf::Event::Closed)
				window.close();
		}
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
				joueur.updatePhysics(elapsed);
				world.Step(1 / FPS, 8, 3);
				joueur.updateVisuel();	
				
				lag -= durationFrame;
			}
		}
		window.clear(sf::Color::Black);
		
		render(lag/durationFrame);
	}
}

void GameManager::render(double timeOnNextFrame)
{
	for (auto &x : joueurs)
	{
		x.draw(window);
			
	}
	window.display();

}

void GameManager::createPatternsFromXml(std::string patternsFile)
{
	pugi::xml_document document;
	if (!document.load_file(patternsFile.c_str()))
	{
		std::cout << "Error lors du loading de " << patternsFile;
	}
	pugi::xml_node doc = document;
	for (pugi::xml_node nod = doc.first_child(); nod; nod = nod.next_sibling()) //on parcourt les patterns
	{
		b2BodyDef bodydef;
		
		bodydef.position.Set(nod.attribute("departX").as_float(), nod.attribute("departY").as_float());
		bodydef.angle = nod.attribute("angle").as_float();
		std::string nom= nod.name(); //Conversion implicite
		if ( nom== "Pattern")
		{
			Pattern newPattern(world, &textureMap[nod.attribute("texture").as_string()], bodydef, b2FixtureDef());
			newPattern.createFromXml(nod,textureMap);
			patternsPossibles.push_back(newPattern);
			
		}
		else
		{
			std::cout << "Pattern mal �crit dans le fichier xml";
		}
	}
	


}
