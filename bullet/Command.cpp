#pragma once
#include "stdafx.h"
#include "Command.h"
#include "Character.h"


void Command::execute()
{
	try
	{
		(character->*method)();
	}
	catch (_exception e)
	{
		std::cout << "ballek";
	}
}
