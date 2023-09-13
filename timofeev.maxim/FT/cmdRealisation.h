#ifndef CMDREALISATION_H
#define CMDREALISATION_H
#include <iostream>
#include "Commands.h"
namespace timofeev
{
  void printHelp(std::istream& in, std::ostream& out, dictsOfDicts &);
  void AddWord(std::istream& in, std::ostream&, dictsOfDicts & dicts);
  void DeleteT(std::istream& in, std::ostream&, dictsOfDicts & dicts);
  void Print(std::istream& in, std::ostream& out, dictsOfDicts & dicts);
}
#endif
