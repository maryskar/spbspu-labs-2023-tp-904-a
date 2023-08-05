#ifndef FT_FUNCS_COMMANDS_H
#define FT_FUNCS_COMMANDS_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include <forward_list>
#include <compare.h>
#include <take_random_elem.h>
#include <sstream>

namespace tarasenko
{
  using namespace std::placeholders;

  template< class Key, class Value, class Compare >
  bool pair_comp(const std::pair< Key, Value >& pair1, const std::pair< Key, Value >& pair2, Compare comp)
  {
    return comp(pair1.first, pair2.first);
  };

  template< class Key, class Value, class Compare >
  std::map< Key, Value, Compare > complement(const std::map< Key, Value, Compare >& lhs,
     const std::map< Key, Value, Compare >& rhs)
  {
    auto comp = std::bind(pair_comp< Key, Value, Compare >, _1, _2, lhs.key_comp());
    std::map< Key, Value, Compare > result(lhs.key_comp());
    std::set_difference(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(),
       std::inserter(result, result.begin()), comp);
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
      auto comp = std::bind(pair_comp< Key, Value, Compare >, _1, _2, lhs.key_comp());
      std::set_intersection(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(),
         std::inserter(result, result.begin()), comp);
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
      auto comp = std::bind(pair_comp< Key, Value, Compare >, _1, _2, lhs.key_comp());
      std::set_union(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(),
         std::inserter(result, result.begin()), comp);
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
      std::for_each(iter, dict.cend(), [&output](const std::pair< Key, Value >& p)
      {
        output << " " << p.first << " " << p.second;
      });
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
    auto key_dict = std::stoll(key);
    bool was_out = false;
    std::for_each(dict_of_dict.cbegin(), dict_of_dict.cend(), [&](const auto& pair)
    {
      if (pair.second.find(key_dict) != pair.second.cend())
      {
        if (was_out)
        {
          output << " ";
        }
        else
        {
          was_out = true;
        }
        output << pair.first;
      }
    });
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
      std::string line = " ";
      std::getline(input, line);
      std::stringstream ss(line);
      using in_iter = std::istream_iterator< std::string >;
      std::copy(in_iter(ss), in_iter(), std::front_inserter(keys));
      return keys;
    }
  }

  template< class Key, class Value, class Compare >
  void deleteDicts(std::istream& input, std::map< std::string,
     std::map< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    std::forward_list< std::string > keys = details::getKeys(input);
    std::for_each(keys.cbegin(), keys.cend(), [&](const std::string& key)
    {
      dict_of_dict.erase(key);
    });
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
    std::for_each(keys.cbegin(), keys.cend(), [&](const std::string& key)
    {
      printDict(out, key, dict_of_dict.at(key)) << "\n";
    });
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
    std::for_each(keys.cbegin(), keys.cend(), [&](const std::string& key)
    {
      dict_of_dict[key][new_key] = new_val;
    });
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
    dict_of_dict[name_new_dict] = dict;
  }

  template< class Key, class Value, class Compare >
  void update(std::map< Key, Value, Compare > &updated, std::map< Key, Value, Compare > &dict)
  {
    if (dict.empty() || updated.empty())
    {
      return;
    }
    std::for_each(updated.begin(), updated.end(), [&](const auto& pair)
    {
      if (dict.find(pair.first) != dict.end())
      {
        updated[pair.first] = dict[pair.first];
      }
    });
  }

  template< class Key, class Value, class Compare >
  void merge(std::map< Key, Value, Compare > &merging, std::map< Key, Value, Compare > &dict)
  {
    if (merging.empty())
    {
      return;
    }
    std::for_each(merging.cbegin(), merging.cend(), [&](const auto& pair)
    {
      dict[pair.first] = merging[pair.first];
    });
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
