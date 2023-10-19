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

namespace tarasenko
{
  using namespace std::placeholders;

  template< class Key, class Value, class Compare >
  bool pair_comp(const std::pair< Key, Value >& pair1, const std::pair< Key, Value >& pair2, Compare comp)
  {
    return comp(pair1.first, pair2.first);
  }

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
  std::map< Key, Value, Compare > merge(const std::map< Key, Value, Compare >& lhs,
     const std::map< Key, Value, Compare >& rhs)
  {
    std::map< Key, Value, Compare > result(lhs.key_comp());
    auto comp = std::bind(pair_comp< Key, Value, Compare >, _1, _2, lhs.key_comp());
    std::merge(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(), std::inserter(result, result.begin()), comp);
    return result;
  }

  namespace details
  {
    template< class Key, class Value >
    void printSpaceKeyValue(std::ostream& output, const std::pair< Key, Value >& p)
    {
      output << " " << p.first << " " << p.second;
    }
  }

  template< class Key, class Value, class Compare >
  std::ostream& printDict(std::ostream& output, const std::string& name_of_dict,
     const std::map< Key, Value, Compare >& dict)
  {
    if (!dict.empty())
    {
      output << name_of_dict;
      auto printData = std::bind(details::printSpaceKeyValue< Key, Value >, std::ref(output), _1);
      std::for_each(dict.cbegin(), dict.cend(), printData);
    }
    return output;
  }


  template< class Key, class Value, class Compare >
  std::istream& operator>>(std::istream& input, std::map< Key, Value, Compare >& dict)
  {
    std::istream::sentry sentry(input);
    if (!sentry)
    {
      return input;
    }
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
      std::string key = "";
      std::for_each(line.begin(), line.end(), [&](char c){
        if (c == ' ')
        {
          if (key != "")
          {
            keys.push_front(key);
            key = "";
          }
        }
        else
        {
          key += c;
        }
      });
      if (key != "")
      {
        keys.push_front(key);
      }
      return keys;
    }
  }

  namespace details
  {
    template< typename Key, typename Value, typename Compare >
    std::map< Key, Value, Compare > resortDict(const std::map< Key, Value, Compare >& dict, Compare comp)
    {
      std::map< Key, Value, Compare > new_dict(comp);
      std::copy(dict.cbegin(), dict.cend(), std::inserter(new_dict, new_dict.begin()));
      return new_dict;
    }
  }

  template< class Key, class Value, class Compare >
  void swap(std::map< Key, Value, Compare >& lhs, std::map< Key, Value, Compare >& rhs)
  {
    lhs.swap(rhs);
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

  namespace details
  {
    template< class Key, class Value, class Compare >
    std::map< Key, Value, Compare > createRandomDict(size_t size, const std::map< Key, Value, Compare >& range)
    {
      std::map< Key, Value, Compare > random_dict(range.key_comp());
      while (random_dict.size() != size)
      {
        auto random_elem = *takeRandomElem(range.cbegin(), range.cend());
        random_dict.insert(random_elem);
      }
      return random_dict;
    }
  }

  template< class Key, class Value, class Compare >
  bool isSubset(const std::map< Key, Value, Compare >& lhs, const std::map< Key, Value, Compare >& rhs)
  {
    auto comp = std::bind(pair_comp< Key, Value, Compare >, _1, _2, lhs.key_comp());
    return std::includes(rhs.cbegin(), rhs.cend(), lhs.cbegin(), lhs.cend(), comp);
  }
}
#endif
