#pragma once
#include "Character.h"
class Character;
class Command
{
	Character *character; 
	void(Character::*method)(); //On passe une reference a une fonction de character
	
public:
	Command(Character* character, void(Character::*method)()) :character(character), method(method) {};
	virtual ~Command() {}
	void execute();
};