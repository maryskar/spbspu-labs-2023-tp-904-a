#ifndef HELP_COMMANDS_H
#define HELP_COMMANDS_H
#include <string>
#include <list>
#include <map>
namespace skarlygina
{
	using List_t = std::list< size_t >;
	using Dict_t = std::map<std::string, List_t>;
	using Dicts_t = std::map<std::string, Dict_t>;

	std::string getWordFromString(std::string&);
	void makeDictStr(std::string, size_t, Dict_t&);
}
#endif
