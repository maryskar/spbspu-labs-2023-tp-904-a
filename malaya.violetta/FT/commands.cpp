#include "commands.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <fstream>
#include "helpFunctions.hpp"
namespace malaya
{
  void info(std::ostream & out)
  {
    out << "INFO - shows all commands and short info about them\n";
    out << "MAN <command> - shows information about one command\n";
    out << "MERGE <dest> <dict1> <dict2> - merges two dictionaries and writes result ";
    out << "to dest dictionary\n";
    out << "GET_INTERSECTION <dest> <dict1> <dict2> - puts same elements of two dictionaries to dest\n";
    out << "SEARCH <dict> <key> - searches the element in dictionary and shows the value\n";
    out << "INSERT <dict> <key> - inserts key to dictionary\n";
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
    out << "INPUT <dict> <filename> - creates new dict and fills it with file contents\n";
  }
  void deleteKey(dictOfDicts & dicts, std::istream & in)
  {
    std::string name, word = " ";
    in >> name >> word;
    Word key(word);
    findDict(dicts, name).erase(key);
  }
  void insert(dictOfDicts & dicts, std::istream & in)
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
  void printDict(const dictionary & dict, std::ostream & out)
  {
    if (!dict.empty())
    {
      using outIt = std::ostream_iterator< dictionary::value_type >;
      std::copy(dict.begin(), dict.end(), outIt(out, " "));
    }
    else
    {
      printNotFound(out);
      out << '\n';
    }
  }
  void print(const dictOfDicts & dicts, std::istream & in, std::ostream & out)
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

  void delDic(dictOfDicts & dicts, std::istream & in)
  {
    std::string name = " ";
    in >> name;
    dicts.erase(name);
  }

  void search(const dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    std::string name, word = " ";
    in >> name >> word;
    Word key(word);
    try
    {
      out << findDict(dicts, name).at(key);
    }
    catch (const std::out_of_range & e)
    {
      printNotFound(out);
      out << '\n';
    }
  }
  const Word & maxElem(const dictionary & dict)
  {
    return std::max_element(dict.begin(), dict.end(), FrequencyComparator{})->first;
  }
  void mostFreq(const dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    std::string name = " ";
    in >> name;
    Word res(maxElem(findDict(dicts, name)));
    if (!res.empty())
    {
      out << res;
    }
    else
    {
      printNotFound(out);
    }
  }
  void areSame(const dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    std::string name1, name2 = " ";
    in >> name1 >> name2;
    const auto & dict1 = findDict(dicts, name1);
    bool result = std::equal(dict1.begin(), dict1.end(), findDict(dicts, name2).begin());
    printYesNo(out, result);
    out << '\n';
  }
  bool includes(const dictionary::value_type & data, const dictionary & dict)
  {
    try
    {
      size_t freq = dict.at(data.first);
      return data.second <= freq;
    }
    catch (const std::out_of_range & e)
    {
      return false;
    }
  }
  void isSubset(const dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    std::string name1, name2 = " ";
    in >> name1 >> name2;
    const auto & dict1 = findDict(dicts, name1);
    const auto & dict2 = findDict(dicts, name2);
    using namespace std::placeholders;
    auto func = std::bind(includes, _1, std::ref(dict2));
    size_t size = std::count_if(dict1.begin(), dict1.end(), func);
    bool result = size == dict1.size();
    printYesNo(out, result);
    out << '\n';
  }
  dictionary::value_type toIntersect(const dictionary::value_type & data, const dictionary & dict)
  {
    try
    {
      size_t num = dict.at(data.first);
      return dictionary::value_type {data.first, std::min(data.second, num)};
    }
    catch (const std::out_of_range & e)
    {
      return dictionary::value_type{Word(""), 0};
    }
  }
  bool isNotEmpty(const dictionary::value_type & data)
  {
    return !data.first.empty();
  }
  void getIntersection(dictOfDicts & dicts, std::istream & in)
  {
    std::string name1, name2, dest = " ";
    in >> dest >> name1 >> name2;
    const auto & dict1 = findDict(dicts, name1);
    const auto & dict2 = findDict(dicts, name2);
    dictionary destDict;
    using namespace std::placeholders;
    auto func = std::bind(toIntersect, _1, std::ref(dict2));
    dictionary tempDict;
    std::transform(dict1.begin(), dict1.end(), std::inserter(tempDict, tempDict.end()), func);
    std::copy_if(tempDict.begin(), tempDict.end(), std::inserter(destDict, destDict.end()), isNotEmpty);
    dicts.insert({dest, destDict});
  }
  void toMerge(const dictionary::value_type & data, dictionary & dict)
  {
    dict[data.first] += data.second;
  }
  void merge(dictOfDicts & dicts, std::istream & in)
  {
    std::string name1, name2, dest = " ";
    in >> dest >> name1 >> name2;
    const auto & dict1 = findDict(dicts, name1);
    const auto & dict2 = findDict(dicts, name2);
    dictionary destDict;
    using namespace std::placeholders;
    auto func = std::bind(toMerge, _1, std::ref(destDict));
    std::for_each(dict1.begin(), dict1.end(), func);
    std::for_each(dict2.begin(), dict2.end(), func);
    dicts.insert({dest, destDict});
  }
  void symmetricDiff(dictionary & dest, const dictionary & dict1, const dictionary & dict2)
  {
    std::set_symmetric_difference(dict1.begin(), dict1.end(),
        dict2.begin(), dict2.end(), std::inserter(dest, dest.end()), WordComparator{});
  }
  void subtract(dictionary & dest, const dictionary & dict1, const dictionary & dict2)
  {
    std::set_difference(dict1.begin(), dict1.end(),
        dict2.begin(), dict2.end(), std::inserter(dest, dest.end()), WordComparator{});
  }
  template < class Function >
  void differences(dictOfDicts & dicts, std::istream & in, Function func)
  {
    std::string name1, name2, dest = " ";
    in >> dest >> name1 >> name2;
    const auto & dict1 = findDict(dicts, name1);
    const auto & dict2 = findDict(dicts, name2);
    dictionary destDict;
    func(destDict, dict1, dict2);
    dicts.insert({dest, destDict});
  }
  void doSymmetricDifference(dictOfDicts & dicts, std::istream & in)
  {
    differences(dicts, in, symmetricDiff);
  }
  void doSubtraction(dictOfDicts & dicts, std::istream & in)
  {
    differences(dicts, in, subtract);
  }
  void insertToDict(const std::string & str, dictionary & dict)
  {
    Word word(str);
    if (!word.empty())
    {
      ++dict[word];
    }
  }
  void input(dictOfDicts & dicts, std::istream & in)
  {
    std::string name = " ";
    in >> name;
    using inIter = std::istream_iterator< std::string >;
    using namespace std::placeholders;
    std::string filename = " ";
    in >> filename;
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
      throw std::invalid_argument("File not found");
    }
    dictionary dic;
    auto func = std::bind(insertToDict, _1, std::ref(dic));
    std::for_each(inIter(inFile), inIter(), func);
    dicts.insert({name, dic});
  }
}
