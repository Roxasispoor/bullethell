#include "stdafx.h"
#include "Pattern.h"
#include "AxialSymmetry.h"
#include "RepeatRotation.h"


void Pattern::deleteAtEndStep()
{
	for(auto &vect:currentBullets)
	{
		vect.erase(
			std::remove_if(vect.begin(), vect.end(),
				[](const Bullet & o) { return o.getToDelete(); }),
			vect.end());
	}
	//On supprime les bullets dans leurs vector, puis le vector si il est vide
	currentBullets.erase(
		std::remove_if(currentBullets.begin(), currentBullets.end(),
			[](const std::vector<Bullet> & o) {return o.size() == 0; }), currentBullets.end());
	
}

void Pattern::createFromXml(pugi::xml_node patternNode, std::map<std::string, sf::Texture>& textureMap)
{
	pugi::xml_node reflectionsNode = patternNode.child("Reflection");
	pugi::xml_node bulletsNode = patternNode.child("Bullets");
	for (pugi::xml_node nod = reflectionsNode.first_child(); nod; nod = nod.next_sibling())
	{
		std::string name = nod.name();//conversion implicite
		if ( name== "SymetrieAxiale")
		{
			
		

			auto s=std::make_shared<AxialSymmetry>
				(nod.attribute("applyOnForce").as_bool(), nod.attribute("centeredOnEnnemy").as_bool(),
					b2Vec2(nod.attribute("departX").as_int(), nod.attribute("departY").as_int()),
					b2Vec2(nod.attribute("directionX").as_int(), nod.attribute("directionY").as_int()));
					reflections.push_back(s);
		}
		else if (name == "Rotation")
		{


				auto s = std::make_shared<RotationOnce>
				(nod.attribute("applyOnForce").as_bool(), nod.attribute("centeredOnEnnemy").as_bool(),
					nod.attribute("numberRepeat").as_int(),
					b2Vec2(nod.attribute("departX").as_int(), nod.attribute("departY").as_int()),
					nod.attribute("angle").as_float()
					);
			reflections.push_back(s);
		}
		
		//nod.attribute("").as_int()
		
	}

	for (pugi::xml_node nod = bulletsNode.first_child(); nod; nod = nod.next_sibling())
	{
			b2BodyDef def;
			def.type = b2_dynamicBody; //this will be a dynamic body
			def.position.Set(nod.attribute("departX").as_float() , nod.attribute("departY").as_float()); //set the starting position
			def.angle = nod.attribute("departY").as_float();
			
			b2FixtureDef fixture;
			std::string attribute = nod.attribute("shape").as_string();
			std::chrono::milliseconds ms1(nod.attribute("temps").as_int());
			
			if (attribute == "Circle")
			{

				std::shared_ptr<b2Shape> shape=std::make_shared<b2CircleShape> ();
				shape->m_radius = nod.attribute("radius").as_float();
				fixture.shape = shape.get();
				
				bullets.push_back(Bullet(*world, &textureMap[nod.attribute("texture").as_string()], def, fixture, nod.attribute("damage").as_float(), nullptr,
					nod.attribute("centerOnEnnemy").as_bool(), nod.attribute("towardEnnemy").as_bool(),shape, std::chrono::high_resolution_clock::duration(ms1)));
			}
				if (attribute == "Rectangle")
				{

					auto shape = std::make_shared<b2PolygonShape>();


					shape->SetAsBox(nod.attribute("width").as_float(), nod.attribute("height").as_float());
					std::shared_ptr<b2Shape> shape2 = shape;
					fixture.shape = shape2.get();
					bullets.push_back(Bullet(*world, &textureMap[nod.attribute("texture").as_string()], def, fixture, nod.attribute("damage").as_float(), nullptr,
						nod.attribute("centerOnEnnemy").as_bool(), nod.attribute("towardEnnemy").as_bool(),shape2, std::chrono::high_resolution_clock::duration(ms1)));
				}
			
	}
}

void Pattern::createShoot()
{
	auto tempsactuel = std::chrono::high_resolution_clock::now(); //On évite de rester a jamais dans la boucle si elle prend trop de temps
	//for (auto &bullet : bullets)
	 if (timer < tempsactuel && isActivated )
	{

		/*std::unique_ptr<Bullet>
			derivedPointer(static_cast<Bullet*>(bullets[bulletIndice].clone().release()));
		*/
		Bullet newBullet(bullets[(bulletIndice+1)%bullets.size()]); // va faire un peu nimp niveau pointeurs vers body, mais osef puisqu'on le réinitialise avec create physical
		currentBullets.push_back(std::vector<Bullet>());
		
		newBullet.setOwner(owner);//les copies font que ça ira bien pour les réflexions

		newBullet.createPhysical();//On rend le bullet physique
		//+= derivedPointer->getElapsed();
		currentBullets[bulletIndice].push_back(newBullet); // O push back APRES l'avoir rendu physique 
		timer += newBullet.getElapsed();
		//currentBullets.push_back(std::move(derivedPointer)); //On move
		Bullet toCopy = std::move(newBullet);
		for (auto &reflection : reflections)
		{
			int aRecopier = currentBullets[bulletIndice].size(); //les symetries scale entre elles
			for (int j=0;j< aRecopier;j++)
			{
				for (int i = 0; i < reflection->getnumberCopies(); i++)
				{
					Bullet currentSymetrised(currentBullets[bulletIndice][j]);
					reflection->applyReflection(currentSymetrised.getBodyDef());
					currentSymetrised.createPhysical();
					currentBullets[bulletIndice].push_back(currentSymetrised);
			
				}
				
			}
		}
	//on ajoute le temps et on update indice
		bulletIndice++;
		if (!isRepeating)
		{
			isActivated = false;
		}
		//On retourne a zero si on repète, on s'arrête sinon
	}
	
		//on verra les reflexions plus tard
//reflected = (((normal dot vecteur) * normal) * 2) + vecteur
	/*	b2Cross(
	for(x:
	}*/
	if (!isRepeating)
	{
		isActivated = false;
	}

}

void Pattern::updatePhysics()
{
	//Si on est activé on shoot ce qu'il faut
	if (isActivated)
	{
		createShoot();
	}
}
