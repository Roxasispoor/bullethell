#include "Box2D/Box2D.h"
#include "Character.h"
#include "Body.h"
class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) {

		//check if fixture A was a ball
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserDataA && bodyUserDataB &&bodyUserDataA!=bodyUserDataB)
		{
			Body * userBodyA= static_cast<Body*>(bodyUserDataA);
Body * userBodyB= static_cast<Body*>(bodyUserDataB);
			userBodyA->preContact(userBodyB);//comme c'est un pointeur on devrait renvoyer le bon type?

		}
		//check if fixture B was a ball
	}

	void EndContact(b2Contact* contact) {

		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserDataA && bodyUserDataB &&bodyUserDataA != bodyUserDataB)
		{
			static_cast<Body*>(bodyUserDataA)->postContact(static_cast<Body*>(bodyUserDataB));//comme c'est un pointeur on devrait renvoyer le bon type?
			static_cast<Body*>(bodyUserDataB)->postContact(static_cast<Body*>(bodyUserDataA));//comme c'est un pointeur on devrait renvoyer le bon type?

		}
	}
};