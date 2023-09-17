#include "sub-commands.hpp"
#include "data-types.hpp"
#include "pred-comp.hpp"

#include <iterator>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <out-msg.hpp>

std::ostream & turkin::add_dict(base_t & base, std::istream & in, std::ostream & out)
{
  std::string dict = "";
  in >> dict;
  base[dict] = {};
  outAddedCMD(out);
  return out;
}

std::ostream & turkin::add_word(base_t & base, std::istream & in, std::ostream & out)
{
  std::string dict = "";
  std::string word = "";
  std::string trns = "";
  in >> dict >> word >> trns;
  base[dict][word] = trns;
  outAddedCMD(out);
  return out;
}

std::ostream & turkin::add_trns(base_t & base, std::istream & in, std::ostream & out)
{
  std::string dict = "";
  std::string word = "";
  std::string trns = "";
  in >> dict >> word >> trns;
  auto & temp = base[dict];
  std::find_if(temp.begin(), temp.end(), isSameTRNS(trns))->second = trns;
  return out;
}


std::ostream & turkin::remove_dict(base_t & base, std::istream & in, std::ostream & out)
{
  std::string dict = "";
  in >> dict;
  base.erase(dict);
  outRemovedCMD(out);
  return out;
}

std::ostream & turkin::remove_word(base_t & base, std::istream & in, std::ostream & out)
{
  std::string dict = "";
  std::string word = "";
  in >> dict >> word;
  base[dict].erase(dict);
  outRemovedCMD(out);
  return out;
}

std::ostream & turkin::remove_trns(base_t & base, std::istream & in, std::ostream & out)
{
  std::string dict = "";
  std::string word = "";
  std::string trns = "";
  in >> dict >> word >> trns;
  auto & temp = base[dict];
  std::find_if(temp.begin(), temp.end(), isSameTRNS(trns))->second = "";
  return out;
}

std::ostream & turkin::find_word(base_t & base, std::istream & in, std::ostream & out)
{
  std::string dict = "";
  std::string word = "";
  in >> dict >> word;
  auto result = base[dict].find(word);
  if (result == base[dict].end())
  {
    outNotFoundedCMD(out);
    return out;
  }
  return out << result;
}

std::ostream & turkin::find_trns(base_t & base, std::istream & in, std::ostream & out)
{
  std::string dict = "";
  std::string word = "";
  std::string trns = "";
  in >> dict >> word >> trns;
  auto & temp = base[dict];
  return out << std::find_if(temp.begin(), temp.end(), isSameTRNS(trns))->second;
}

std::ostream & turkin::count_word(base_t & base, std::istream & in, std::ostream & out)
{
  std::string dict = "";
  std::string word = "";
  in >> dict >> word;
  return out << base[dict].count(word);
}

std::ostream & turkin::count_trns(base_t & base, std::istream & in, std::ostream & out)
{
  std::string dict = "";
  std::string word = "";
  std::string trns = "";
  in >> dict >> word >> trns;
  auto & temp = base[dict];
  return out << std::count_if(temp.begin(), temp.end(), isSameTRNS(trns));
}

std::ostream & turkin::save_file(base_t & base, std::istream & in, std::ostream & out)
{
  std::string dict = "";
  std::string path = "";
  in >> dict >> path;
  std::ofstream file(path);
  if (!file.is_open())
  {
    throw std::runtime_error("cannot open file");
  }
  auto & temp = base[dict];
  std::copy(temp.begin(), temp.end(), std::ostream_iterator< word_pair_t >(file, "\n"));
  return out;
}

std::ostream & turkin::save_out(base_t & base, std::istream & in, std::ostream & out)
{
  std::string dict = "";
  in >> dict;
  auto & temp = base[dict];
  std::copy(temp.begin(), temp.end(), std::ostream_iterator< word_pair_t >(out, "\n"));
  return out;
}

std::ostream & turkin::help_add(base_t &, std::istream &, std::ostream & out)
{
  out << "CMD:\n";
  out << "ADD DICT|WORD|TRNS\n";
  out << "ADD DICT <DICT NAME>\n";
  out << "ADD WORD <DICT NAME> <WORD> <TRNS>";
  out << "ADD TRNS <DICT NAME> <WORD> <TRNS>";
  return out;
}

std::ostream & turkin::help_remove(base_t &, std::istream &, std::ostream & out)
{
  out << "CMD:\n";
  out << "REMOVE DICT|WORD|TRNS\n";
  out << "REMOVE DICT <DICT NAME>\n";
  out << "REMOVE WORD <DICT NAME> <WORD> <TRNS>";
  out << "REMOVE TRNS <DICT NAME> <WORD> <TRNS>";
  return out;
}

std::ostream & turkin::help_find(base_t &, std::istream &, std::ostream & out)
{
  out << "CMD:\n";
  out << "FIND DICT|WORD|TRNS\n";
  out << "FIND DICT <DICT NAME>\n";
  out << "FIND WORD <DICT NAME> <WORD> <TRNS>";
  out << "FIND TRNS <DICT NAME> <WORD> <TRNS>";
  return out;
}

std::ostream & turkin::help_count(base_t &, std::istream &, std::ostream & out)
{
  out << "CMD:\n";
  out << "COUNT WORD|TRNS\n";
  out << "COUNT WORD <DICT NAME> <WORD> <TRNS>";
  out << "COUNT TRNS <DICT NAME> <WORD> <TRNS>";
  return out;
}

std::ostream & turkin::help_save(base_t &, std::istream &, std::ostream & out)
{
  out << "CMD:\n";
  out << "SAVE FILE|OUT\n";
  out << "SAVE FILE <FILE NAME>\n";
  out << "SAVE OUT";
  return out;
}

std::ostream & turkin::help_default(base_t &, std::istream &, std::ostream & out)
{
  out << "CMD:\n";
  out << "HELP ADD|REMOVE|FIND|COUNT|SAVE\n";
  return out;
}
