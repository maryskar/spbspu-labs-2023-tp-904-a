#ifndef FT_COMMANDS_H
#define FT_COMMANDS_H
#include <iostream>
#include <vector>
#include <map>

using en_word_t = std::string;
using ru_vector_t = std::vector< std::string >;
using dict_t = std::map< en_word_t, ru_vector_t >;
using dictOfDicts = std::map< std::string, dict_t >;
std::string insertCommand(std::istream &);
class Commands
{
public:
  Commands();
  void doCommand(const std::string &command, std::ostream &out) const;
  void doCommand(const std::string &command, std::istream &in, dictOfDicts &dict) const;
  void doCommand(const std::string &command, dictOfDicts &, std::ostream &out) const;
  void doCommand(const std::string &command, const std::string &, dictOfDicts &, std::ostream &out) const;
  void doCommand(const std::string &command, const std::string &, dictOfDicts &) const;
private:
  using firstFunc_ = void(*)(const dictOfDicts &, std::ostream &);
  using secondFunc_ = void(*)(const std::string &, dictOfDicts &, std::ostream &);
  using thirdFunc_ = void(*)(const std::string &, dictOfDicts &);
  std::map< std::string, void(*)(std::ostream &) > dict1_;
  std::map< std::string, void(*)(std::istream &, dictOfDicts &) > dict2_;
  std::map< std::string, firstFunc_ > dict3_;
  std::map< std::string, secondFunc_ > dict4_;
  std::map< std::string, thirdFunc_ > dict5_;
};
void executeCommand(std::ostream &out, std::istream &in, Commands &commands, dictOfDicts &dicts, dict_t &dict, std::string command, std::string &);
void help(std::ostream &);
void createDictionary(std::istream &in, dictOfDicts &dicts);

//void outDictionaries(dictOfDicts dicts, std::ostream &);
void outDictionaries(const dictOfDicts &dicts, std::ostream &out);

//void translate(const std::string&, dictOfDicts &, std::ostream&);
void translate(const std::string& input, dictOfDicts &dicts, std::ostream &out);
//void doIntersect(const std::string& str, dictOfDicts & dicts);
#endif
