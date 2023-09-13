#ifndef FT_HELPFUNCTION_H
#define FT_HELPFUNCTION_H
#include <map>
#include <iostream>
#include <vector>
namespace timofeev
{
  using dict_t = std::map< std::string, std::vector<std::string> >;
  void readDict(std::istream& in, dict_t& dict);
  void delTrans(std::istream& in, dict_t& dict);
  std::ostream& printInvalid(std::ostream &out);
}
#endif //FT_HELPFUNCTION_H
