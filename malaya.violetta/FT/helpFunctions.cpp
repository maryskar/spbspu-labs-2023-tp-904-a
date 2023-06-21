#include "helpFunctions.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
namespace malaya
{
  std::ostream & printNotFound(std::ostream & out)
  {
    out << "<NOT FOUND>";
    return out;
  }
  std::ostream & printInvalid(std::ostream & out)
  {
    out << "<INVALID COMMAND>";
    return out;
  }
  std::ostream & printYesNo(std::ostream & out, bool number)
  {
    return number ? out << "YES" : out << "NO";
  }
  dictionary & findDict(dictOfDicts & dicts, const std::string & name)
  {
    return dicts.at(name);
  }

}