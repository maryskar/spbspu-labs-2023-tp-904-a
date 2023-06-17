#include "commands.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cctype>

namespace malaya
{
  void info(std::ostream & out)
  {
    out << "INFO - shows all commands and short info about them\n";
    out << "MAN <command> - shows full information about command\n";
    out << "MERGE <dest> <dict1> <dict2> - merges two dictionaries and writes result ";
    out << "to dest dictionary\n";
    out << "GET_INTERSECTION <dest> <dict1> <dict2> - puts same elements of two dictionaries to dest\n";
    out << "SEARCH <dict> <key> - searches the element in dictionary and shows the value\n";
    out << "INSERTS <dict> <key> - inserts key to dictionary\n";
    out << "DELETE_KEY <dict> <key> - deletes key from dictionary\n";
    out << "DELETE_DICT <dict> <key> - deletes dictionary\n";
    out << "PRINT <dict> - prints all keys from dictionaries with their values\n";
    out << "ARE_SAME <dict1> <dict2> - checks if two dictionaries are identical\n";
    out << "DO_SYMMETRIC_DIFFERENCE <dest> <dict1> <dict2> - fills new dest dictionary ";
    out << "with symmetric difference of two dictionaries\n";
    out << "SUBTRACT <dest> <dict1> <dict2> - fills new dest dictionary with subtraction ";
    out << "of two dictionaries\n";
    out << "FIND_MOST_FREQUENT <dict1> - shows the most frequent word in the dict\n";
    out << "IS_SUBSET <dict1> <dict2> - checks if one dictionary is subset of another\n";
  }
  void deleteKey(dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    std::string name, word = " ";
    in >> name >> word;
    Word key(word);
    findDict(dicts, name).erase(key);
  }
  void insert(dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    std::string name, word = " ";
    in >> name >> word;
    Word key(word);
    if (!key.empty())
    {
      ++findDict(dicts, name)[key];
    }
    else
    {
      throw std::invalid_argument("Incorrect word");
    }
  }
  std::ostream & operator<<(std::ostream & out, const std::pair< const std::string, size_t > & data)
  {
    std::ostream::sentry ostreamChecker(out);
    if (!ostreamChecker)
    {
      return out;
    }
    out << data.first << " " << data.second;
    return out;
  }
  void printDict(const dictionary & dict, std::ostream & out)
  {
    if(!dict.empty())
    {
      using outIt = std::ostream_iterator< dictionary::value_type >;
      std::copy(dict.begin(), dict.end(), outIt(out, "\n"));
    }
    else
    {
      printNotFound(out);
      out << '\n';
    }
  }
  void print(dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    std::string name = " ";
    in >> name;
    printDict(findDict(dicts, name), out);
  }

  void man(const descriptDict & comms, std::istream & in, std::ostream & out)
  {
    std::string name = " ";
    in >> name;
    out << comms.at(name);
  }

  void delDic(dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    std::string name = " ";
    in >> name;
    dicts.erase(name);
  }

  void search(dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    std::string name, word = " ";
    in >> name >> word;
    Word key(word);
    out << findDict(dicts, name).at(key); //разные исключения?
  }
  const Word & maxElem(const dictionary & dict)
  {
    return std::max_element(dict.begin(), dict.end(), FrequencyComparator{})->first;
  }
  void mostFreq(dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    std::string name = " ";
    in >> name;
    out << maxElem(findDict(dicts, name));
  }
  void areSame(dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    std::string name1, name2 = " ";
    in >> name1 >> name2;
    const auto & dict1 = findDict(dicts, name1);
    bool result = std::equal(dict1.begin(), dict1.end(), findDict(dicts, name2).begin());
    printYesNo(out, result);
    out << '\n';
  }
}