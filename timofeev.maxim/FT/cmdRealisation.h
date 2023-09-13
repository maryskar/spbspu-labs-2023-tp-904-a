#ifndef CMDREALISATION_H
#define CMDREALISATION_H
#include <iostream>
#include "Commands.h"
namespace timofeev
{
  void printHelp(std::istream& in, std::ostream& out, dictsOfDicts&);
  void AddWord(std::istream& in, std::ostream& out, dictsOfDicts& dicts);
  void DeleteT(std::istream& in, std::ostream& out, dictsOfDicts& dicts);
  void Print(std::istream& in, std::ostream& out, dictsOfDicts& dicts);
  void Delete(std::istream& in, std::ostream& out, dictsOfDicts& dicts);
  void Translate(std::istream& in, std::ostream& out, dictsOfDicts& dicts);
  void Exist(std::istream& in, std::ostream& out, dictsOfDicts& dicts);
  void Common(std::istream&, std::ostream& out, dictsOfDicts& dicts);
}
#endif
