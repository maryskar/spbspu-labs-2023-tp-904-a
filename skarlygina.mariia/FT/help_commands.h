#ifndef HELP_COMMANDS_H
#define HELP_COMMANDS_H
#include <string>
#include "commands.h"
namespace skarlygina
{
	std::string getWordFromString(std::string&);
	void makeDictStr(std::string, size_t, Dict_t&);
}
#endif
