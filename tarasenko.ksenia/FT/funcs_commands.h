#ifndef FT_FUNCS_COMMANDS_H
#define FT_FUNCS_COMMANDS_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <forward_list>
#include <functional>
#include <compare.h>
#include <take_random_elem.h>
#include <algorithm>

namespace tarasenko
{
  template< class Key, class Value, class Compare >
  std::map< Key, Value, Compare > complement(const std::map< Key, Value, Compare >& lhs,
     const std::map< Key, Value, Compare >& rhs)
  {
    auto result = lhs;
    if (!lhs.empty() && !rhs.empty())
    {
      auto iter_lhs = lhs.cbegin();
      for (; iter_lhs != lhs.cend(); iter_lhs++)
      {
        if (rhs.find(iter_lhs->first) != rhs.cend())
        {
          result.erase(iter_lhs->first);
        }
      }
    }
    return result;
  }

  template< class Key, class Value, class Compare >
  std::map< Key, Value, Compare > intersect(const std::map< Key, Value, Compare >& lhs,
     const std::map< Key, Value, Compare >& rhs)
  {
    if (rhs.empty())
    {
      return rhs;
    }
    std::map< Key, Value, Compare > result(lhs.key_comp());
    if (!lhs.empty())
    {
      auto iter_lhs = lhs.cbegin();
      for (; iter_lhs != lhs.cend(); iter_lhs++)
      {
        if (rhs.find(iter_lhs->first) != rhs.cend())
        {
          result.insert({iter_lhs->first, iter_lhs->second});
        }
      }
    }
    return result;
  }

  template< class Key, class Value, class Compare >
  std::map< Key, Value, Compare > unionWith(const std::map< Key, Value, Compare >& lhs,
     const std::map< Key, Value, Compare >& rhs)
  {
    if (lhs.empty())
    {
      return rhs;
    }
    auto result = lhs;
    if (!rhs.empty())
    {
      auto iter_rhs = rhs.cbegin();
      for (; iter_rhs != rhs.cend(); iter_rhs++)
      {
        if (lhs.find(iter_rhs->first) == lhs.cend())
        {
          result.insert({iter_rhs->first, iter_rhs->second});
        }
      }
    }
    return result;
  }

  template< class Key, class Value, class Compare >
  std::ostream& printDict(std::ostream& output, const std::string& name_of_dict,
     const std::map< Key, Value, Compare >& dict)
  {
    if (!dict.empty())
    {
      output << name_of_dict << " ";
      auto iter = dict.cbegin();
      output << iter->first << " " << iter->second;
      ++iter;
      while (iter != dict.cend())
      {
        output << " " << iter->first << " " << iter->second;
        ++iter;
      }
    }
    return output;
  }

  template< class Key, class Value, class Compare >
  std::ostream& print(std::ostream& output, const std::string& name_of_dict,
     const std::map< std::string, std::map< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    std::map< Key, Value, Compare > given_dict = dict_of_dict.at(name_of_dict);
    if (given_dict.empty())
    {
      throw std::invalid_argument("Empty");
    }
    printDict(output, name_of_dict, given_dict) << "\n";
    return output;
  }

  template< class Key, class Value, class Compare >
  std::ostream& printIf(std::ostream& output, const std::string& key,
     const std::map< std::string, std::map< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    auto it = dict_of_dict.cbegin();
    auto key_dict = std::stoll(key);
    bool was_out = false;
    for (; it != dict_of_dict.cend(); it++)
    {
      if (it->second.find(key_dict) != it->second.cend())
      {
        if (was_out)
        {
          output << " " << it->first;
        }
        else
        {
          output << it->first;
          was_out = true;
        }
      }
    }
    return output << "\n";
  }

  template< class Key, class Value, class Compare >
  std::istream& operator>>(std::istream& input, std::map< Key, Value, Compare >& dict)
  {
    Key key;
    Value value;
    while (input >> key >> value)
    {
      dict.insert({key, value});
    }
    return input;
  }

  template< class Key, class Value, class Compare >
  void add(std::istream& input, std::map< Key, Value, Compare >& dict)
  {
    while (input)
    {
      char begin = ' ';
      input >> begin;
      if (begin != '(')
      {
        input.putback(begin);
        break;
      }
      char end = ' ';
      while (input >> end)
      {
        if (end == ')')
        {
          break;
        }
        else
        {
          input.putback(end);
        }
        Key key;
        Value value;
        input >> key >> value;
        dict.insert({key, value});
        input.clear();
      }
    }
  }

  namespace details
  {
    std::forward_list< std::string > getKeys(std::istream& input)
    {
      std::forward_list< std::string > keys;
      std::string line;
      std::getline(input, line);
      std::string key = "";
      for (size_t i = 0; i < line.size(); i++)
      {
        if (line[i] == ' ')
        {
          if (key != "")
          {
            keys.push_front(key);
            key = "";
          }
        }
        else
        {
          key += line[i];
        }
      }
      if (key != "")
      {
        keys.push_front(key);
      }
      return keys;
    }
  }

  template< class Key, class Value, class Compare >
  void deleteDicts(std::istream& input, std::map< std::string,
     std::map< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    std::forward_list< std::string > keys = details::getKeys(input);
    for (auto i: keys)
    {
      dict_of_dict.erase(i);
    }
  }

  template< class Key, class Value, class Compare >
  void writeDicts(std::istream& input, std::map< std::string,
     std::map< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    std::string filename = " ";
    input >> filename;
    std::ofstream out;
    out.open(filename);
    if (!out.is_open())
    {
      throw std::invalid_argument("File not found");
    }
    std::forward_list< std::string > keys = details::getKeys(input);
    for (auto i: keys)
    {
      printDict(out, i, dict_of_dict.at(i)) << "\n";
    }
  }

  namespace details
  {
    template< typename Key, typename Value, typename Compare >
    std::map< Key, Value, Compare > resortDict(std::map< Key, Value, Compare >& dict, Compare comp)
    {
      std::map< Key, Value, Compare > new_dict(comp);
      std::copy(dict.begin(), dict.end(), std::inserter(new_dict, new_dict.begin()));
      return new_dict;
    }
  }

  template< class Key, class Value, class Compare >
  void resort(std::istream& input, std::map< std::string,
     std::map< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    std::string sort = " ";
    input >> sort;
    Comp comp;
    if (sort == "ascending")
    {
      Comp ascending(std::less<>{});
      comp = ascending;
    }
    else if (sort == "descending")
    {
      Comp descending(std::greater<>{});
      comp = descending;
    }
    else
    {
      throw std::invalid_argument("Invalid command");
    }
    std::for_each(dict_of_dict.begin(), dict_of_dict.end(), [&](auto& pair)
    {
      dict_of_dict[pair.first] = details::resortDict(pair.second, comp);
    });
  }

  template< class Key, class Value, class Compare >
  void put(std::istream& input, std::map< std::string,
     std::map< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    Key new_key;
    Value new_val;
    input >> new_key >> new_val;
    if (!input)
    {
      throw std::invalid_argument("Incorrect data");
    }
    std::forward_list< std::string > keys = details::getKeys(input);
    for (auto i: keys)
    {
      dict_of_dict[i].insert({new_key, new_val});
    }
  }

  template< class Key, class Value, class Compare >
  void swap(std::map< Key, Value, Compare >& lhs, std::map< Key, Value, Compare >& rhs)
  {
    lhs.swap(rhs);
  }

  template< class Key, class Value, class Compare >
  void copy(std::istream& input, std::map< std::string,
     std::map< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    std::string name_dict = " ";
    std::string name_new_dict = " ";
    input >> name_dict >> name_new_dict;
    auto dict = dict_of_dict.at(name_dict);
    dict_of_dict.insert({name_new_dict, dict});
  }

  template< class Key, class Value, class Compare >
  void update(std::map< Key, Value, Compare > &updated, std::map< Key, Value, Compare > &dict)
  {
    if (dict.empty() || updated.empty())
    {
      return;
    }
    auto it = updated.begin();
    for (; it != updated.end(); it++)
    {
      if (dict.find(it->first) != dict.end())
      {
        updated[it->first] = dict[it->first];
      }
    }
  }

  template< class Key, class Value, class Compare >
  void merge(std::map< Key, Value, Compare > &merging, std::map< Key, Value, Compare > &dict)
  {
    if (merging.empty())
    {
      return;
    }
    auto it = merging.begin();
    for (; it != merging.end(); it++)
    {
      if (dict.find(it->first) != dict.end())
      {
        dict[it->first] = merging[it->first];
      }
      else
      {
        dict.insert(*it);
      }
    }
  }

  template< class Key, class Value, class Compare >
  void addRandomDict(std::istream& input, std::map< std::string,
     std::map< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    std::string name_new_dict = " ";
    size_t size = 0;
    input >> name_new_dict >> size;
    if (!input)
    {
      throw std::invalid_argument("Incorrect data");
    }
    std::forward_list< std::string > names_of_dicts = details::getKeys(input);

    std::map< Key, Value, Compare > dict_of_elems;
    auto i = names_of_dicts.begin();
    for (; i != names_of_dicts.end(); i++)
    {
      auto dict = dict_of_dict.at(*i);
      for (auto j = dict.begin(); j != dict.end(); j++)
      {
        dict_of_elems.insert(*j);
      }
    }
    if (dict_of_elems.size() < size)
    {
      throw std::invalid_argument("Not enough elements");
    }

    std::map< Key, Value, Compare > random_dict;
    while (random_dict.size() != size)
    {
      auto random_elem = *takeRandomElem(dict_of_elems.begin(), dict_of_elems.end());
      random_dict.insert(random_elem);
    }
    dict_of_dict.insert({name_new_dict, random_dict});
  }

  template< class Key, class Value, class Compare >
  bool isSubset(const std::map< Key, Value, Compare >& lhs, const std::map< Key, Value, Compare >& rhs)
  {
    if (lhs.empty() || rhs.empty())
    {
      return false;
    }
    auto it = lhs.cbegin();
    for (; it != lhs.cend(); it++)
    {
      if (rhs.find(it->first) == rhs.cend())
      {
        return false;
      }
    }
    return true;
  }
}
#endif
