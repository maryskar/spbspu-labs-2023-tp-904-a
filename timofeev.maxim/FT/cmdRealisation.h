#ifndef CMDREALISATION_H
#define CMDREALISATION_H
#include <iostream>
#include "Commands.h"
namespace timofeev
{
  void printHelp(std::istream& in, std::ostream& out, dictsOfDicts &);
  void AddWord(std::istream& in, std::ostream&, dictsOfDicts & dicts);
  void DeleteW(std::istream& in, std::ostream&, dictsOfDicts & dicts);
}
#endif
