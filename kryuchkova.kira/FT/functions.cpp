#include "functions.h"
#include <istream>
#include <iterator>
#include <functional>
#include <algorithm>

namespace kryuchkova
{
  bool hasDictWithName(const std::map< std::string, ErDictionary > & dicts, const std::string name)
  {
    return dicts.find(name) != dicts.end();
  }

  void doCreate(std::istream & in, std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    if (hasDictWithName(dicts, name))
    {
      throw std::logic_error("Dict with this name already exists");
    }
    dicts[name] = ErDictionary();
  }

  void doInsert(std::istream & in, std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    ErDictionary::word word;
    in >> word;
    ErDictionary::translations trans;
    std::string data;
    while (std::getline(in, data, ' '))
    {
      trans.push_back(data);
    }
    auto iter = dicts.find(name);
    if (!hasDictWithName(dicts, name))
    {
      throw std::logic_error("No such dicts with this name");
    }
    else
    {
      iter->second.insert(word, trans);
    }
  }

  void doSearch(std::istream & in, std::ostream & out, std::map< std::string, ErDictionary > & dicts)
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
    ErDictionary dict = dicts.find(name)->second;
    dict.erase(word);
  }

  void fillDict(std::istream & in, ErDictionary & dict);
  void findByFirstLet(std::istream & in, ErDictionary & dict);
  void printDict(std::ostream & out, const ErDictionary & dict);
  void exportDict(std::istream & in, ErDictionary & dict);

  void unite(const ErDictionary & dict1, const ErDictionary & dict2)
  {
    ErDictionary new_dict;
    std::set_union(dict1.begin(), dict1.end(), dict2.begin(), dict2.end(), std::back_inserter(new_dict));
  }

  void intersect(ErDictionary new_dict, const ErDictionary & dict1, const ErDictionary & dict2)
  {
    ErDictionary new_dict;
    std::set_intersection(dict1.begin(), dict1.end(), dict2.begin(), dict2.end(), std::back_inserter(new_dict));
  }

  void symSubtract(ErDictionary new_dict, const ErDictionary & dict1, const ErDictionary & dict2)
  {
    ErDictionary new_dict;
    std::set_symmetric_difference(dict1.begin(), dict1.end(), dict2.begin(), dict2.end(), std::back_inserter(new_dict));
  }

  void subtract(ErDictionary new_dict, const ErDictionary & dict1, const ErDictionary & dict2)
  {
    ErDictionary new_dict;
    std::set_difference(dict1.begin(), dict1.end(), dict2.begin(), dict2.end(), std::back_inserter(new_dict));
  }

  bool addition(const ErDictionary & dict1, const ErDictionary & dict2)
  {
    ErDictionary new_dict;
    return std::includes(dict1.begin(), dict1.end(), dict2.begin(), dict2.end());
  }

}