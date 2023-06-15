#include "commands.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <functional>
#include "helpFunctions.hpp"

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
    std::string name, key = " ";
    in >> name >> key;
    findDict(dicts, name).erase(key);
  }
  bool isLetter(unsigned char symbol)
  {
    return std::isalpha(symbol);
  }
  std::string strFilter(const std::string & str)
  {
    std::string result = "";
    std::copy_if(str.begin(), str.end(), result.begin(), isLetter);
    return result;
  }
  void insert(dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    std::string name, key = " ";
    in >> name >> key;
    key = strFilter(key);
    if (!key.empty())
    {
      ++findDict(dicts, name)[key];
    }
    else
    {
      throw std::invalid_argument("Incorrect word");
    }
  }
  std::ostream & operator<<(std::ostream & out,
    const std::pair< std::string, size_t > & data)
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
    using outIt = std::ostream_iterator< std::pair< std::string, size_t > >;
    //std::copy(dict.begin(), dict.end(), outIt(out, "\n"));
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

  void search(dictOfDicts & dicts, const std::string & name,
              const std::string & key, std::ostream & out)
  {
    out << findDict(dicts, name).at(key); //разные исключения?
  }
}