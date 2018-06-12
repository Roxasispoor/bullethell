#include "stdafx.h"
#include "GameManager.h"




GameManager::GameManager()
	:gravity(0, 0), world(gravity), textureMap(),
	window(sf::VideoMode(1920, 1080), "Bullet heaven", sf::Style::Fullscreen) {
	srand(time(NULL));


	world.SetContactListener(&listenner);
	listenner.setGameManager(this);
	
	
	for (auto x : aliasFichierNames) //On remplit les textures et on les mets a jour
	{

		textureMap[x.second];
		if (!textureMap[x.second].loadFromFile(x.first))
		{
			std::cout << "erreur de chargement de " << x.first;
		}
	}
	createPatternsFromXml("../patterns.xml");
	b2FixtureDef fixturePlayer;
	b2CircleShape shapePlayer;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody; //this will be a dynamic body
	shapePlayer.m_radius = 5;

	fixturePlayer.shape = &shapePlayer; //sera copiée, np
	//Initialise un joueur, et son pattern
	joueurs.push_back(Player(world, &textureMap["joueur"], bodyDef,
		fixturePlayer, std::make_shared<b2CircleShape>(shapePlayer), 100.f));
	
	joueurs[0].createPhysical();
	joueurs[0].getPatterns().push_back(patternsPossibles[1]);
	joueurs[0].getPatterns()[0].setOwner(&joueurs[0]);


//On load les ennemis et on leur donne les patterns qu'il faut

	pugi::xml_document documentEnnemies;
	if (!documentEnnemies.load_file("../ennemies.xml"))
	{
		std::cout << "Error lors du loading de ennemies";
	}
	pugi::xml_node docEnnemies = documentEnnemies;

	for (pugi::xml_node nod = docEnnemies.first_child(); nod; nod = nod.next_sibling())
	{
		b2BodyDef ennemydef;
		b2FixtureDef fixtureEnnemy;
		ennemydef.position.x = nod.attribute("departX").as_float();
		ennemydef.position.y = nod.attribute("departY").as_float();
		ennemydef.angle = nod.attribute("angle").as_float();

		std::string forme = nod.attribute("shape").as_string();
		if (forme == "Circle")
		{

			std::shared_ptr<b2Shape> shape = std::make_shared<b2CircleShape>();
			shape->m_radius = nod.attribute("radius").as_float();
			fixtureEnnemy.shape = shape.get();


			Ennemy ennemi(world, &textureMap[nod.attribute("texture").as_string()], ennemydef, fixtureEnnemy, shape, nod.attribute("life").as_float());

			for (pugi::xml_node nodie = nod.first_child(); nodie; nodie = nodie.next_sibling())
			{
				int numPattern = nodie.attribute("value").as_int();
				if (numPattern < patternsPossibles.size())
				{
					ennemi.getPatterns().push_back(patternsPossibles[numPattern]);
					ennemi.getPatterns()[ennemi.getPatterns().size() - 1].setOwner(&ennemi);
					ennemi.getPatterns()[ennemi.getPatterns().size() - 1].createPhysical();
				}

			}


			ennemisPossibles.push_back(std::move(ennemi));
		}
		if (forme == "Rectangle")
		{

			auto shape = std::make_shared<b2PolygonShape>();
			shape->SetAsBox(nod.attribute("width").as_float(), nod.attribute("height").as_float());

			std::shared_ptr<b2Shape> shape2 = shape;
			Ennemy ennemi(world, &textureMap[nod.attribute("texture").as_string()], ennemydef, fixtureEnnemy, shape2, nod.attribute("life").as_float());

			fixtureEnnemy.shape = shape2.get();

			for (pugi::xml_node nodie = nod.first_child(); nodie; nodie = nodie.next_sibling())
			{
				int numPattern = nodie.attribute("value").as_int();
				if (numPattern < patternsPossibles.size())
				{
					ennemi.getPatterns().push_back(patternsPossibles[numPattern]);
					ennemi.getPatterns()[ennemi.getPatterns().size() - 1].setOwner(&ennemi);
					ennemi.getPatterns()[ennemi.getPatterns().size() - 1].createPhysical();
				}

			}
			ennemisPossibles.push_back(std::move(ennemi));
			ennemisPossibles[ennemisPossibles.size() - 1].getPatterns()[ennemi.getPatterns().size() - 1].setOwner(&ennemisPossibles[ennemisPossibles.size() - 1]);
		}

	}

};



void GameManager::mainLoop()
{
	sf::Font font;
	if (!font.loadFromFile("../arial.ttf"))
	{
		std::cout << "error loading font";
		// error...
	}
	sf::Text text;

	// select the font
	text.setFont(font);

	sf::Music music;
	if (!music.openFromFile("../Evil Approach.wav"))
	{
		std::cout << "music loading failed";
	}
	music.setLoop(true);
	music.play();
	
	ennemisEnVie.push_back(ennemisPossibles[0]);//*(static_cast<Ennemy*>(ennemisPossibles[0].clone().get())));
	ennemisEnVie[0].createPhysical();
	//maraboutage pour faire tourner le pattern
	patternsPossibles[0].getBodyDef().angularVelocity = 2.0f;
	ennemisEnVie[0].getPatterns()[0].createPhysical();
	ennemisEnVie[0].getPatterns()[0].getB2Body()->SetAngularVelocity(2.f);

	for (auto &patterns : ennemisEnVie[0].getPatterns())
	{
		patterns.setOwner(&ennemisEnVie[0]);
	}
	auto previous = std::chrono::system_clock::now();
	std::chrono::duration<double> durationFrame(1 / FPS);
	std::chrono::duration<double> lag;
		while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		auto current = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = current - previous;
		//Si on a trop de frame de retard
		previous = current;
		lag += elapsed;
		
		while (lag >= durationFrame);
		{
			for (auto &joueur : joueurs)
			{
				joueur.input();

				joueur.updateVisuel();
				joueur.updatePhysics(elapsed);
				
				
				lag -= durationFrame;
			}
			for (auto& ennemy : ennemisEnVie)
			{

				ennemisEnVie[0].input();
				ennemy.updatePhysics(elapsed);
				ennemy.updateVisuel();
			}
			world.Step(1 / FPS, 2, 0);

			window.clear(sf::Color::Black);
			for (auto &joueur : joueurs)
			{
				if (joueur.isDead())
				{
					text.setFillColor(sf::Color::Red);
					text.setCharacterSize(24);
					text.setPosition(300, 300);
					text.setString("YOU LOSE");
					text.setStyle(sf::Text::Bold | sf::Text::Underlined);
					window.draw(text);
				}
				for (auto &pattern : joueur.getPatterns())
				{

					pattern.deleteAtEndStep();
				}
			}
			for (auto &ennemi : ennemisEnVie)
			{
				if (ennemi.isDead())
				{
					text.setFillColor(sf::Color::Red);
					text.setCharacterSize(24);
					text.setPosition(800, 300);
					text.setString("YOU WIN");
					window.draw(text);
				}
				for (auto &pattern : ennemi.getPatterns())
				{
					pattern.deleteAtEndStep();
				}
			}
			render(lag / durationFrame);

		}

	}
}

void GameManager::render(double timeOnNextFrame)
{
	
	for (auto &x : joueurs)
	{
		x.draw(window);
			
	}
	for (auto &ennemy : ennemisEnVie)
	{
		ennemy.draw(window);

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

		b2FixtureDef fixdef;
		std::shared_ptr<b2Shape> shape = std::make_shared<b2CircleShape>();
		shape->m_radius = 5;
		fixdef.shape = shape.get();
		bodydef.type = b2_dynamicBody; //this will be a dynamic body
//		shapePlayer.m_radius = 5;

		


		bodydef.position.Set(nod.attribute("departX").as_float(), nod.attribute("departY").as_float());
		bodydef.angle = nod.attribute("angle").as_float();
		std::string nom= nod.name(); //Conversion implicite
		if ( nom== "Pattern")
		{
			Pattern newPattern(world, &textureMap[nod.attribute("texture").as_string()], bodydef, fixdef,shape);
			newPattern.getBodyDef().angularVelocity = 2.0f;
			newPattern.createFromXml(nod,textureMap);
			patternsPossibles.push_back(newPattern);

		}
		else
		{
			std::cout << "Pattern mal écrit dans le fichier xml";
		}
	}
	


}
