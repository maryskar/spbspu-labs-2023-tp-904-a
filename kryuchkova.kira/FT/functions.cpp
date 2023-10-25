#include "functions.h"
#include <istream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <fstream>
#include <functional>
#include <vector>
#include <iostream>
#include <IOstructs.h>

namespace kryuchkova
{

  bool isSameLetter(char letter, std::pair< ErDictionary::word, ErDictionary::translations > word_and_translation)
  {
    return letter == word_and_translation.first.at(0);
  }

  bool hasDictWithName(const std::map< std::string, ErDictionary > & dicts, const std::string name)
  {
    return dicts.find(name) != dicts.end();
  }

  std::pair< ErDictionary, ErDictionary > getDicts(std::istream & in, std::map< std::string, ErDictionary > & dicts)
  {
    std::string name1;
    in >> name1;
    std::string name2;
    in >> name2;
    if (!hasDictWithName(dicts, name1) || !hasDictWithName(dicts, name2))
    {
      throw std::logic_error("No such dicts with this name");
    }
    ErDictionary dict1 = dicts.find(name1)->second;
    ErDictionary dict2 = dicts.find(name2)->second;
    return std::pair< ErDictionary, ErDictionary >(dict1, dict2);
  }

  void doCreate(std::istream & in, std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    if (hasDictWithName(dicts, name))
    {
      throw std::logic_error("Dict with this name already exists");
    }
    ErDictionary dict(name);
    dicts[name] = dict;
  }

  void doInsert(std::istream & in, std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    ErDictionary::word word;
    in >> word;
    int n_translations;
    in >> n_translations;
    ErDictionary::translations trans;
    std::copy_n(std::istream_iterator< std::string >(in), n_translations, std::back_inserter(trans));
    auto iter = dicts.find(name);
    if (!hasDictWithName(dicts, name))
    {
      throw std::logic_error("No such dicts with this name");
    }
    iter->second.insert(word, trans);
  }

  void doSearch(std::istream & in, std::ostream & out, const std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    std::string word;
    in >> word;
    if (!hasDictWithName(dicts, name))
    {
      throw std::logic_error("No such dicts with this name");
    }
    ErDictionary dict = dicts.find(name)->second;
    ErDictionary::translations res = dict.find(word);
    out << word << ": ";
    std::copy(res.begin(), res.end(), std::ostream_iterator< std::string >(out, " "));
  }

  void doDelete(std::istream & in, std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    std::string word;
    in >> word;
    if (!hasDictWithName(dicts, name))
    {
      throw std::logic_error("No such dicts with this name");
    }
    dicts.find(name)->second.erase(word);
  }

  void fillDict(std::istream & in, std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    ErDictionary dict = dicts.find(name)->second;
    std::string file_name;
    in >> file_name;
    std::ifstream file;
    file.open(file_name);
    file >> dict;
    file.close();
    dicts[name] = dict;
  }

  void findByFirstLet(std::istream & in, std::ostream & out, const std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    char letter;
    in >> letter;
    if (!hasDictWithName(dicts, name))
    {
      throw std::logic_error("No such dicts with this name");
    }
    using namespace std::placeholders;
    auto func = std::bind(isSameLetter, letter, _1);
    ErDictionary dict = dicts.find(name)->second;
    std::map< std::string, std::vector< std::string > > new_dict;
    std::map< std::string, std::vector< std::string > > dict_words = dict.getDict();
    std::copy_if(dict_words.begin(), dict_words.end(), std::inserter(new_dict, new_dict.end()), func);
    ErDictionary letter_dict(name, new_dict);
    out << letter_dict;
  }

  void printDict(std::istream & in, std::ostream & out, const std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    if (!hasDictWithName(dicts, name))
    {
      throw std::logic_error("No such dicts with this name");
    }
    ErDictionary dict = dicts.find(name)->second;
    out << dict;
  }

  void exportDict(std::istream & in, const std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    if (!hasDictWithName(dicts, name))
    {
      throw std::logic_error("No such dicts with this name");
    }
    ErDictionary dict = dicts.find(name)->second;
    std::string file_name;
    in >> file_name;
    std::ofstream file(file_name);
    file << dict;
    file.close();
  };

  void unite(std::istream & in, std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    std::pair< ErDictionary, ErDictionary > res = getDicts(in, dicts);
    std::map< ErDictionary::word, ErDictionary::translations > dict1 = res.first.getDict();
    std::map< ErDictionary::word, ErDictionary::translations > dict2 = res.second.getDict();
    std::map< ErDictionary::word, ErDictionary::translations > new_dict;
    std::set_union(dict1.begin(), dict1.end(), dict2.begin(), dict2.end(), std::inserter(new_dict, new_dict.end()));
    dicts[name] = ErDictionary(name, new_dict);
  }

  void intersect(std::istream & in, std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    std::pair< ErDictionary, ErDictionary > res = getDicts(in, dicts);
    std::map< ErDictionary::word, ErDictionary::translations > dict1 = res.first.getDict();
    std::map< ErDictionary::word, ErDictionary::translations > dict2 = res.second.getDict();
    std::map< ErDictionary::word, ErDictionary::translations > new_dict;
    std::set_intersection(dict1.begin(), dict1.end(), dict2.begin(), dict2.end(), std::inserter(new_dict, new_dict.end()));
    dicts[name] = ErDictionary(name, new_dict);
  }

  void symSubtract(std::istream & in, std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    std::pair< ErDictionary, ErDictionary > res = getDicts(in, dicts);
    std::map< ErDictionary::word, ErDictionary::translations > dict1 = res.first.getDict();
    std::map< ErDictionary::word, ErDictionary::translations > dict2 = res.second.getDict();
    std::map< ErDictionary::word, ErDictionary::translations > new_dict;
    std::set_symmetric_difference(dict1.begin(), dict1.end(), dict2.begin(), dict2.end(), std::inserter(new_dict, new_dict.end()));
    dicts[name] = ErDictionary(name, new_dict);
  }

  void subtract(std::istream & in, std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    std::pair< ErDictionary, ErDictionary > res = getDicts(in, dicts);
    std::map< ErDictionary::word, ErDictionary::translations > dict1 = res.first.getDict();
    std::map< ErDictionary::word, ErDictionary::translations > dict2 = res.second.getDict();
    std::map< ErDictionary::word, ErDictionary::translations > new_dict;
    std::set_difference(dict1.begin(), dict1.end(), dict2.begin(), dict2.end(), std::inserter(new_dict, new_dict.end()));
    dicts[name] = ErDictionary(name, new_dict);
  }

  void addition(std::istream & in, std::ostream & out, std::map< std::string, ErDictionary > & dicts)
  {
    std::pair< ErDictionary, ErDictionary > res = getDicts(in, dicts);
    std::map< ErDictionary::word, ErDictionary::translations > dict1 = res.first.getDict();
    std::map< ErDictionary::word, ErDictionary::translations > dict2 = res.second.getDict();
    std::map< ErDictionary::word, ErDictionary::translations > new_dict;
    out << std::includes(dict1.begin(), dict1.end(), dict2.begin(), dict2.end());
  }
}
