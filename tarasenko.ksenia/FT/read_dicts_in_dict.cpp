#include "read_dicts_in_dict.h"

void tarasenko::readDictsInDict(std::istream& input, std::map< std::string, dict_t, std::greater<> >& dict_of_dict)
{
  while (input)
  {
    std::string name_of_dict = "";
    while (input >> name_of_dict)
    {
      size_t key;
      std::string value;
      dict_t dict;
      while (input >> key >> value)
      {
        dict.insert({key, value});
      }
      dict_of_dict.insert({name_of_dict, dict});
      input.clear();
    }
  }
}
