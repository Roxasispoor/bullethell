#pragma once
#include "Body.h"
#include "Character.h"
#include <vector>
#include "Ennemy.h"
#include "Player.h"
#include <chrono>
#include "MyContactListenner.h"
#include "const.h"


class GameManager
{

	
public:
	GameManager() :gravity(0, 0), world(gravity),textureMap(),
		window(sf::VideoMode(1920, 1080), "Bullet heaven", sf::Style::Fullscreen) {
		world.SetContactListener(&listenner);
		listenner.setGameManager(this);
		//world.SetDebugDraw(
			//world.SetDebugDraw();
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
		joueurs.push_back(Player (world, &textureMap["joueur"], bodyDef, 
			fixturePlayer,std::make_shared<b2CircleShape>(shapePlayer),100.f));
		joueurs[0].createPhysical();

		joueurs[0].getPatterns().push_back(patternsPossibles[0]);
		joueurs[0].getPatterns()[0].setOwner(&joueurs[0]);
		//On donne un pattern au joueur
		


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


				Ennemy ennemi(world, &textureMap[nod.attribute("texture").as_string()], ennemydef, fixtureEnnemy,shape,nod.attribute("life").as_float());
//				ennemi.setShape(shape);
				for (pugi::xml_node nodie = nod.first_child(); nodie; nodie = nodie.next_sibling())
				{
					int numPattern = nodie.attribute("value").as_int();
					if (numPattern < patternsPossibles.size() )
					{
						ennemi.getPatterns().push_back(patternsPossibles[numPattern]);
						ennemi.getPatterns()[ennemi.getPatterns().size()-1].setOwner(&ennemi);
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
				Ennemy ennemi(world, &textureMap[nod.attribute("texture").as_string()], ennemydef, fixtureEnnemy,shape2, nod.attribute("life").as_float());
				
				//ennemi.setShape(shape2);
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
				ennemisPossibles[ennemisPossibles.size()-1].getPatterns()[ennemi.getPatterns().size() - 1].setOwner(&ennemisPossibles[ennemisPossibles.size() - 1]);
			}
			
		}
		//joueurs[0].setTextureActuelle(&textureMap["joueur"]);
		};//on remplira la texture du joueur juste après les avoir load
	~GameManager();
	void mainLoop();
	void render(double timeOnNextFrame);
	void createPatternsFromXml(std::string patternsFile);

private:
	//const std::pair<std::string, std::string>aliasFichiers = { ["blah","blah"] };
	
	std::map<std::string, std::string> aliasFichierNames = { {"../joueur.png","joueur"},{"../bullets.png","bullet"},{ "../laser.png","laser"},{"../ghostmaiden.png","ghostmaiden"} };
	b2World world;

	std::vector<Pattern> patternsPossibles;
	//Player joueur;
	std::map<std::string, sf::Texture> textureMap;
	std::vector<Player> joueurs;
	std::vector<Ennemy> ennemisPossibles;
	std::vector<Ennemy> ennemisEnVie;
	b2Vec2 gravity; //nogravity
	MyContactListener listenner;
	sf::RenderWindow window;

	bool doSleep = true;
};
	