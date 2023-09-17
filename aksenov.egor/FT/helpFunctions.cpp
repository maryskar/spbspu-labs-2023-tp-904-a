#include "helpFunctions.h"
#include <string>
#include <functional>
#include <algorithm>
std::string getNextWord(std::string& str, char delimeter)
{
  size_t next_space = str.find_first_of(delimeter);
  std::string word = str.substr(0, next_space);
  str.erase(0, ((next_space == str.npos) ? next_space : next_space + 1));
  return word;
}

ru_vector_t splitStringToTranslation(std::string str)
{
  ru_vector_t ru_list;
  while (!str.empty())
  {
    ru_list.push_back(getNextWord(str, ','));
  }
  return ru_list;
}

void outRuList(const ru_vector_t& list, std::ostream& out, const char* delimeter)
{
  out << '[';
  bool is_first = true;
  for (auto&& ru: list)
  {
    if (!is_first)
    {
      out << delimeter;
    }
    is_first = false;
    out << ru;
  }
  out << ']' << "\n";
}

void outDict(const dict_t& dict, std::ostream& out, const char* delimeter)
{
  bool is_first = true;
  for (auto &&en_ru: dict) {
    if (!is_first) {
      out << '\n';
    }
    is_first = false;
    out << en_ru.first << ' ';
    outRuList(en_ru.second, out, delimeter);
  }
  out << "\n";
}
bool isValidDict(const std::string& name, const dictOfDicts &dicts)
{
  return dicts.find(name) != dicts.end();
}

void prepareString(std::string& str)
{
  size_t first_not_whitespace = str.find_first_not_of(' ');
  str.erase(0, first_not_whitespace);
}

std::vector< std::string > getNamesFromString(std::string str)
{
  prepareString(str);
  std::vector< std::string > names;
  while (!str.empty())
  {
    names.push_back(getNextWord(str));
  }
  return names;
}

bool isValidDicts(const std::vector< std::string >& names, const dictOfDicts &dicts)
{
  using namespace std::placeholders;
  return std::all_of(names.begin(), names.end(), std::bind(isValidDict, std::placeholders::_1, std::ref(dicts)));
}

ru_vector_t intersectRuList(const ru_vector_t& first, const ru_vector_t& second)
{
  ru_vector_t new_list;
  std::set_intersection(first.begin(), first.end(), second.begin(), second.end(), std::inserter(new_list, new_list.end()));
  return new_list;
}

dict_t intersectDicts(const dict_t& first, const dict_t& second)
{
  dict_t new_dict;
  auto cmp_less = KeysCmp< dict_t::key_compare >{};
  std::set_intersection(first.begin(), first.end(), second.begin(), second.end(), std::inserter(new_dict, new_dict.end()), cmp_less);

  std::for_each(new_dict.begin(), new_dict.end(),
                [&second](dict_t::value_type& pair)
                {
                    pair.second = intersectRuList(pair.second, second.at(pair.first));
                });

  return new_dict;
}