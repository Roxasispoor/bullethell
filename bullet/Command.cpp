#pragma once
#include "stdafx.h"
#include "Command.h"
#include "Character.h"

void Command::execute()
{
	(character->*method)();
}
