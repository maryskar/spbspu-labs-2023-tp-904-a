#ifndef FT_HELPFUNCTION_H
#define FT_HELPFUNCTION_H
#include <map>
#include <iostream>
#include <vector>
namespace timofeev
{
  using dict_t = std::map< std::string, std::vector<std::string> >;
  void readDict(std::istream& in, std::ostream& out, dict_t& dict);
  void delTrans(std::istream& in, std::ostream &out, dict_t& dict);
  std::ostream& printInvalid(std::ostream& out);
  std::ostream& printEmpty(std::ostream& out);
  void printDict(std::ostream& out, dict_t& dict);
  void printList(const std::vector < std::string >& list, std::ostream& out);
  void delDict(dict_t& dict);
  void delList(std::vector < std::string >& list);
  void findTrans(std::ostream& out, const std::string& word, dict_t& dict);
}
#endif //FT_HELPFUNCTION_H
