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
				if (attribute == "Circle")
			{

				auto shape=std::make_shared<b2CircleShape> ();
				shape->m_radius = nod.attribute("radius").as_float();
				fixture.shape = shape.get();
				bullets.push_back(Bullet(*world, &textureMap[nod.attribute("texture").as_string()], def, fixture, nod.attribute("damage").as_float(), nullptr,
					nod.attribute("centerOnEnnemy").as_bool(), nod.attribute("towardEnnemy").as_bool()));
			}
				if (attribute == "Rectangle")
				{

					auto shape = std::make_shared<b2PolygonShape>();
					shape->SetAsBox(nod.attribute("width").as_float(), nod.attribute("height").as_float());
					fixture.shape = shape.get();
					bullets.push_back(Bullet(*world, &textureMap[nod.attribute("texture").as_string()], def, fixture, nod.attribute("damage").as_float(), nullptr,
						nod.attribute("centerOnEnnemy").as_bool(), nod.attribute("towardEnnemy").as_bool()));
				}
			
	}
}

//... Ah la bonne non covenance sur les pointeurs intelligents 
void Pattern::createShoot()
{
	auto tempsactuel = std::chrono::high_resolution_clock::now(); //On évite de rester a jamais dans la boucle si elle prend trop de temps
	//for (auto &bullet : bullets)
	while (timer < tempsactuel)
	{

		/*std::unique_ptr<Bullet>
			derivedPointer(static_cast<Bullet*>(bullets[bulletIndice].clone().release()));
		*/
		Bullet newBullet(bullets[bulletIndice]); // va faire un peu nimp niveau pointeurs vers body, mais osef puisqu'on le réinitialise avec create physical
		currentBullets.push_back(std::vector<Bullet>());
			currentBullets[bulletIndice].push_back(newBullet);
		newBullet.createPhysical();//On rend le bullet physique
		//+= derivedPointer->getElapsed();
		timer += newBullet.getElapsed();
		//currentBullets.push_back(std::move(derivedPointer)); //On move
		
		for (auto &x : reflections)
		{
			for (auto& bullet : currentBullets[bulletIndice])
			{
				Bullet BulletToCopy = bullet;
				for (int i = 0; i < x->getnumberCopies(); i++)
				{
					Bullet newBullet(BulletToCopy);

					x->applyReflection(newBullet.getBodyDef());

					currentBullets[bulletIndice].push_back(newBullet);
					newBullet.createPhysical();

					BulletToCopy = newBullet; // On se décale par rapport au précédent
				}
			}
//			x->applyReflection();
		//	derivedPointer->createPhysical();//On rend le bullet physique
											 //+= derivedPointer->getElapsed();
			//timer += derivedPointer->getElapsed();
		}
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
