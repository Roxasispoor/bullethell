#include "Box2D/Box2D.h"
#include "Character.h"
#include "Body.h"
class GameManager;
class MyContactListener : public b2ContactListener
{
public:	
	/// <summary>
	///uses a double dispatch to find which one collided
	/// </summary>
	/// <param name="contact"></param>
	/// Called when two fixtures begin to touch.
	void BeginContact(b2Contact* contact) {
	b2Fixture* a = contact->GetFixtureA();
		void* bodyUserDataA = a->GetBody()->GetUserData();
   void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserDataA && bodyUserDataB &&bodyUserDataA!=bodyUserDataB )
		{
			Body * userBodyA= static_cast<Body*>(bodyUserDataA);
			Body * userBodyB= static_cast<Body*>(bodyUserDataB);
			if (userBodyA->isValid() && userBodyB->isValid())
			{
				userBodyB->preContact(userBodyA);//comme c'est un pointeur on devrait renvoyer le bon type?
			}
		}
		//check if fixture B was a ball
	};	
	/// <summary> Not implemented
	/// </summary>
	/// <param name="contact"></param>
	/// Called when two fixtures cease to touch.
	void EndContact(b2Contact* contact) {

		/*void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserDataA && bodyUserDataB &&bodyUserDataA != bodyUserDataB)
		{
			static_cast<Body*>(bodyUserDataA)->postContact(static_cast<Body*>(bodyUserDataB));//comme c'est un pointeur on devrait renvoyer le bon type?
			static_cast<Body*>(bodyUserDataB)->postContact(static_cast<Body*>(bodyUserDataA));//comme c'est un pointeur on devrait renvoyer le bon type?

		}*/
	};


	void setGameManager(GameManager* gm) {
		gameManager = gm;
	};

private:
	GameManager* gameManager;


};