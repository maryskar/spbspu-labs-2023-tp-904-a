#ifndef CMDREALISATION_H
#define CMDREALISATION_H
#include <iostream>
#include "Commands.h"
namespace timofeev
{
  void doCreateDict(std::istream& in, std::ostream&, dictsOfDicts& dicts);
  void doPrintHelp(std::istream& in, std::ostream& out, dictsOfDicts&);
  void doAddWord(std::istream& in, std::ostream& out, dictsOfDicts& dicts);
  void doDeleteT(std::istream& in, std::ostream& out, dictsOfDicts& dicts);
  void doPrint(std::istream& in, std::ostream& out, dictsOfDicts& dicts);
  void doDelete(std::istream& in, std::ostream&, dictsOfDicts& dicts);
  void doTranslate(std::istream& in, std::ostream& out, dictsOfDicts& dicts);
  void doExist(std::istream& in, std::ostream& out, dictsOfDicts& dicts);
  void doCommon(std::istream&, std::ostream& out, dictsOfDicts& dicts);
}
#endif
