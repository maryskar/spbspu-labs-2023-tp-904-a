#include "create-commands-maps.hpp"
#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>

namespace chemodurov
{
  std::ostream & outEmpty(std::ostream & out)
  {
    return out << "<EMPTY>";
  }

  std::ostream & outInvalidCommand(std::ostream & out)
  {
    return out << "<INVALID COMMAND>";
  }

  std::string getWordFromString(const std::string & data)
  {
    size_t space_ind = data.find(' ');
    std::string word;
    if (space_ind == std::string::npos)
    {
      word = data;
    }
    else if (!space_ind)
    {
      word = ' ' + getWordFromString(data.substr(1));
    }
    else
    {
      word = data.substr(0, space_ind);
    }
    return word;
  }

  template< typename F >
  F traverseString(const std::string & data, F f)
  {
    size_t read = 0;
    while (read < data.size())
    {
      std::string word_str = getWordFromString(data.substr(read));
      read += word_str.size() + 1;
      f(word_str);
    }
    return f;
  }

  void helpCommand(std::ostream & out)
  {
    out << "Available commands:\n";
    out << "1. \"help\" - prints this info\n";
    out << "2. \"read <dataset> <text>\" - reads text into dataset\n";
    out << "3. \"read_file <dataset> <filename>\" - reads text from file into dataset\n";
    out << "4. \"print <dataset...>\" - prints data from datasets\n";
    out << "5. \"complement <new_dataset> <dataset...>\" - complements data from datasets to new_dataset\n";
    out << "6. \"intersect <new_dataset> <dataset...>\" - intersects data from datasets to new_dataset\n";
    out << "7. \"union <new_dataset> <dataset...>\" - unions data from datasets to new_dataset\n";
    out << "8. \"top <number> <dataset>\" - prints top <number> most frequency words from dataset\n";
    out << "8. \"insert <dataset> <word> <frequency>\" - inserts word with frequency into dataset\n";
    out << "10. \"search <dataset> <word>\" - search word into dataset and print it frequency\n";
    out << "11. \"delete_word <dataset> <word>\" - deletes word from dataset\n";
    out << "12. \"delete_dataset <dataset...>\" - deletes datasets\n";
    out << "13. \"make <dataset>\" - makes dataset if no exist\n";
    out << "14. \"drop <dataset1> <dataset2\" - drops from dataset1 words that in dataset2\n";
  }

  void readWordToDict(FreqDict & dict, const std::string & word)
  {
    try
    {
      ++(dict[Word(word)]);
    }
    catch (const std::invalid_argument & e)
    {}
  }

  void readCommand(std::istream & in, DictWithFreqDicts & data)
  {
    std::string name_dic;
    in >> name_dic;
    std::string line;
    std::getline(in, line);
    if (!in)
    {
      throw std::invalid_argument("Invalid read command");
    }
    using namespace std::placeholders;
    auto func = std::bind(readWordToDict, std::ref(data.at(name_dic)), _1);
    traverseString(line, func);
  }

  void readFileCommand(std::istream & in, DictWithFreqDicts & data)
  {
    std::string name_dic;
    in >> name_dic;
    std::string filename;
    in >> filename;
    if (!in)
    {
      throw std::invalid_argument("Invalid read_file command");
    }
    std::ifstream input(filename);
    if (!input.is_open())
    {
      throw std::invalid_argument("Invalid read_file command");
    }
    auto & dict = data.at(name_dic);
    do
    {
      input >> filename;
      try
      {
        ++(dict[Word(filename)]);
      }
      catch (const std::invalid_argument & e)
      {}
    }
    while (input);
  }

  void printDictFromString(std::ostream & out, const DictWithFreqDicts & data, const std::string & line)
  {
    const auto & dic = data.at(line);
    if (!dic.empty())
    {
      out << line << ' ';
      {
        using chemodurov::ios::SpecialDataIO;
        using out_it_t = std::ostream_iterator< SpecialDataIO >;
        std::copy(dic.begin(), dic.end(), out_it_t(out, " "));
      }
    }
    else
    {
      outEmpty(out);
    }
    out << '\n';
  }

  void printCommand(std::istream & in, std::ostream & out, const DictWithFreqDicts & data)
  {
    std::string line;
    in.ignore(1);
    std::getline(in, line);
    if (!in || line.empty())
    {
      throw std::invalid_argument("Invalid print command");
    }
    using namespace std::placeholders;
    auto func = std::bind(printDictFromString, std::ref(out), std::cref(data), _1);
    traverseString(line, func);
  }

  void complementDicts(const DictWithFreqDicts & data, FreqDict & lhs, const std::string & rhs)
  {
    const auto & rhs_dict = data.at(rhs);
    bool need_check_first = true;
    for (auto i = lhs.begin(); i != lhs.end(); ++i)
    {
      auto it = rhs_dict.find(i->first);
      if (it != rhs_dict.end())
      {
        if (i->second <= it->second)
        {
          lhs.erase(i);
          i = lhs.begin();
        }
        else
        {
          i->second -= it->second;
          need_check_first = false;
        }
      }
      else
      {
        need_check_first = false;
      }
    }
    if (!lhs.empty() && need_check_first)
    {
      auto it = rhs_dict.find(lhs.begin()->first);
      if (it != rhs_dict.end())
      {
        if (lhs.begin()->second <= it->second)
        {
          lhs.erase(lhs.begin());
        }
        else
        {
          lhs.begin()->second -= it->second;
        }
      }
    }
  }

  template< typename P >
  void complementOrIntersectOrUnionCommand(std::istream & in, DictWithFreqDicts & data, P p)
  {
    std::string name_res;
    in >> name_res;
    std::string name_lhs;
    in >> name_lhs;
    std::string line;
    in.ignore(1);
    std::getline(in, line);
    if (!in || line.empty())
    {
      throw std::invalid_argument("Invalid complement command");
    }
    FreqDict res = data.at(name_lhs);
    using namespace std::placeholders;
    auto func = std::bind(p, std::cref(data), std::ref(res), _1);
    traverseString(line, func);
    data.insert({name_res, res});
  }

  void complementCommand(std::istream & in, DictWithFreqDicts & data)
  {
    complementOrIntersectOrUnionCommand(in, data, complementDicts);
  }

  void intersectDicts(const DictWithFreqDicts & data, FreqDict & lhs, const std::string & rhs)
  {
    const auto & rhs_dict = data.at(rhs);
    for (auto i = lhs.begin(); i != lhs.end(); ++i)
    {
      auto it = rhs_dict.find(i->first);
      if (it != rhs_dict.end())
      {
        i->second = std::min(i->second, it->second);
      }
      else
      {
        lhs.erase(i);
        i = lhs.begin();
      }
    }
    if (!lhs.empty())
    {
      auto it = rhs_dict.find(lhs.begin()->first);
      if (it != rhs_dict.end())
      {
        lhs.begin()->second = std::min(lhs.begin()->second, it->second);
      }
      else
      {
        lhs.erase(lhs.begin());
      }
    }
  }

  void intersectCommand(std::istream & in, DictWithFreqDicts & data)
  {
    complementOrIntersectOrUnionCommand(in, data, intersectDicts);
  }

  void unionDicts(const DictWithFreqDicts & data, FreqDict & lhs, const std::string & rhs)
  {
    const auto & rhs_dict = data.at(rhs);
    for (auto & i : lhs)
    {
      auto it = rhs_dict.find(i.first);
      if (it != rhs_dict.end())
      {
        i.second = i.second + it->second;
      }
    }
    for (const auto & i : rhs_dict)
    {
      auto it = lhs.find(i.first);
      if (it == lhs.end())
      {
        lhs.insert(i);
      }
    }
  }

  void unionCommand(std::istream & in, DictWithFreqDicts & data)
  {
    complementOrIntersectOrUnionCommand(in, data, unionDicts);
  }

  template< typename ForwardIt >
  bool isGreaterSizeT(ForwardIt lhs, ForwardIt rhs)
  {
    return lhs->second > rhs->second;
  }

  std::string transformPair(const FreqDict::const_iterator & iter)
  {
    std::string res;
    res = iter->first.getWord();
    res += ' ' + std::to_string(iter->second);
    return res;
  }

  void topCommand(std::istream & in, std::ostream & out, const DictWithFreqDicts & data)
  {
    size_t num = 0;
    in >> num;
    std::string name_dict;
    in >> name_dict;
    if (!in || !num)
    {
      throw std::invalid_argument("Invalid top command");
    }
    const auto & dict = data.at(name_dict);
    size_t iters_size = 0;
    using iter_t = FreqDict::const_iterator;
    auto iters = std::vector< iter_t >(dict.size());
    for (auto i = dict.begin(); i != dict.end(); ++i)
    {
      iters[iters_size++] = i;
    }
    using iter_on_iter_t = std::vector< iter_t >::iterator;
    using compare_t = decltype(isGreaterSizeT< iter_t >);
    std::sort< iter_on_iter_t, compare_t >(iters.begin(), iters.end(), isGreaterSizeT);
    size_t to_print = std::min(num, iters_size);
    using out_it_t = std::ostream_iterator< std::string >;
    std::transform(iters.begin(), iters.begin() + to_print, out_it_t(out, " "), transformPair);
    out << '\n';
  }

  void insertCommand(std::istream & in, DictWithFreqDicts & data)
  {
    std::string name_dict;
    in >> name_dict;
    std::string word;
    in >> word;
    size_t freq = 0;
    in >> freq;
    if (!in || !freq)
    {
      throw std::invalid_argument("Invalid insert command");
    }
    (data[name_dict])[Word(word)] = freq;
  }

  void searchCommand(std::istream & in, std::ostream & out, const DictWithFreqDicts & data)
  {
    std::string name_dict;
    in >> name_dict;
    std::string word;
    in >> word;
    if (!in)
    {
      throw std::invalid_argument("Invalid search command");
    }
    const FreqDict & dict = data.at(name_dict);
    try
    {
      out << dict.at(Word(word)) << '\n';
    }
    catch (const std::out_of_range & e)
    {
      out << "0\n";
    }
  }

  void deleteWordCommand(std::istream & in, DictWithFreqDicts & data)
  {
    std::string name_dict;
    in >> name_dict;
    std::string word;
    in >> word;
    data.at(name_dict).at(Word(word));
    data.at(name_dict).erase(Word(word));
  }

  void eraseDicts(DictWithFreqDicts & data, const std::string & name)
  {
    data.at(name);
    data.erase(name);
  }

  void deleteDatasetCommand(std::istream & in, DictWithFreqDicts & data)
  {
    std::string line;
    in.ignore(1);
    std::getline(in, line);
    if (!in || line.empty())
    {
      throw std::invalid_argument("Invalid delete_dataset command");
    }
    using namespace std::placeholders;
    auto func = std::bind(eraseDicts, std::ref(data), _1);
    traverseString(line, func);
  }

  void makeCommand(std::istream & in, DictWithFreqDicts & data)
  {
    std::string name_dict;
    in >> name_dict;
    if (!in)
    {
      throw std::invalid_argument("Invalid make command");
    }
    data[name_dict];
  }

  void dropCommand(std::istream & in, DictWithFreqDicts & data)
  {
    std::string name_to_drop;
    in >> name_to_drop;
    std::string name_words_from;
    in >> name_words_from;
    if (!in)
    {
      throw std::invalid_argument("Invalid drop command");
    }
    auto & to_drop = data.at(name_to_drop);
    const auto & words_from = data.at(name_words_from);
    for (const auto & i : words_from)
    {
      to_drop.erase(i.first);
    }
  }

  CommandsMaps::CommandsMaps():
   fst_map_(),
   snd_map_(),
   trd_map_()
  {
    fst_map_.insert({"help", helpCommand});
    snd_map_.insert({"read", readCommand});
    snd_map_.insert({"read_file", readFileCommand});
    snd_map_.insert({"complement", complementCommand});
    snd_map_.insert({"intersect", intersectCommand});
    snd_map_.insert({"union", unionCommand});
    snd_map_.insert({"insert", insertCommand});
    snd_map_.insert({"delete_word", deleteWordCommand});
    snd_map_.insert({"delete_dataset", deleteDatasetCommand});
    snd_map_.insert({"make", makeCommand});
    snd_map_.insert({"drop", dropCommand});
    trd_map_.insert({"print", printCommand});
    trd_map_.insert({"top", topCommand});
    trd_map_.insert({"search", searchCommand});
  }

  void CommandsMaps::doCommand(const std::string & name_cmd, std::ostream & out) const
  {
    fst_map_.at(name_cmd)(out);
  }

  void CommandsMaps::doCommand(const std::string & name_cmd, std::istream & in, DictWithFreqDicts & data) const
  {
    snd_map_.at(name_cmd)(in, data);
  }

  void CommandsMaps::doCommand(const std::string & name_cmd,
      std::istream & in,
      std::ostream & out,
      const DictWithFreqDicts & data) const
  {
    trd_map_.at(name_cmd)(in, out, data);
  }
}
