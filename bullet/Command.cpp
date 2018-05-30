#include "Command.h"

void Command::execute()
{
	(character->*method)();
}
