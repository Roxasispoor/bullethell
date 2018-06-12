#pragma once
class Character;
/// <summary>
/// Pattern Command permettant de stocker les input du joueur, de l'ia... Utilise un pointeur vers méthode Character
/// </summary>
class Command
{
	Character *character; 
	void(Character::*method)(); //On passe une reference a une fonction de character
	
public:
	Command(Character* character, void(Character::*method)()) :character(character), method(method) {};
	virtual ~Command() {}
	void execute();
};