#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>
namespace skarlygina
{
	void analyze(std::string&, Dicts_t&);
	void printDict(std::string&, Dicts_t&);
	void writelnFile(std::string&, Dicts_t&);
	void printWord(std::string&, Dicts_t&);
	void deleteWord(std::string&, Dicts_t&);
	void deleteDict(std::string&, Dicts_t&);
	void merge(std::string&, Dicts_t&);
	void intersect(std::string&, Dicts_t&);
	void rename(std::string&, Dicts_t&);
	void complement(std::string&, Dicts_t&);
}
#endif
