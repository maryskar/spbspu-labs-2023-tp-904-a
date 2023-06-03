#include "helpFunctions.hpp"
#include <iostream>
namespace malaya
{
  void printNotFound(std::ostream & out)
  {
    out << "Dictionary not found\n";
  }
  void printInvalid(std::ostream & out)
  {
    out << "<INVALID COMMAND>\n";
  }

  dictionary & findDict(dictOfDicts & dicts, const std::string & name)
  {
    return dicts.at(name);
  }
}