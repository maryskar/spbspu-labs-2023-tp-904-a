#ifndef FT_DICTIONARY_HPP
#define FT_DICTIONARY_HPP
#include <map>
#include <string>
class Dictionary
{
public:
  Dictionary();
  void insert(const std::string& word);
//private:
  std::map< std::string, size_t > dict_;
};


#endif