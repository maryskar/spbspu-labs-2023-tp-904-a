#ifndef HELP_COMMANDS_H
#define HELP_COMMANDS_H
#include <string>
#include <list>
#include <map>
#include <vector>
namespace skarlygina
{
	using List_t = std::list< size_t >;
	using Dict_t = std::map< std::string, List_t >;
	using Dicts_t = std::map< std::string, Dict_t >;
	using Vector_t = std::vector< std::string >;

	std::string getWordFromString(std::string&);
	void makeDictStr(std::string, size_t, Dict_t&);
	std::ostream& doPrint(const Dict_t&, std::ostream&);
	void doWriteInFile(const Dict_t&, const std::string&);
	Dict_t doIntersect(const std::string&, const std::string&, Dicts_t&);
	Dict_t doComplement(const std::string&, const std::string&, Dicts_t&);
}
#endif
