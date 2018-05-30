#pragma once
#include "Character.h"
/// <summary>
/// Character qui peut recevoir les input utilisateurs + mana et autres.
/// </summary>
/// <seealso cref="Character" />
class Player :
	public Character
{
public:
	void input();
	void update();
	Player();
	~Player();
};

