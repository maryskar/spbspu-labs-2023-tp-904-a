#ifndef COMMANDS_H
#define COMMANDS_H
#include <map>
#include <vector>
#include <iostream>
using dictOfTranslations = std::map<std::string, std::vector<std::string>>;
using dictOfDicts = std::map<std::string, dictOfTranslations>;

std::string insertCommand(std::istream &);

class Commands{
public:
  Commands();
  void doCommand(const std::string &command, std::istream &in, dictOfDicts &dict);
  void doCommand(const std::string &command, const dictOfDicts &dict, std::ostream &out);
  void doCommand(const std::string &command, std::istream &in, dictOfDicts &dict, std::ostream &out);
  void doCommand(const std::string &command, std::ostream &out);
private:
  using firstFunc_ = void(*)(std::istream &, dictOfDicts &);
  using secondFunc_ = void(*)(const dictOfDicts &, std::ostream &);
  using thirdFunc_ = void(*)(std::istream &, dictOfDicts &, std::ostream &);
  std::map< std::string, firstFunc_ > dict1_;
  std::map< std::string, secondFunc_ > dict2_;
  std::map< std::string, thirdFunc_ > dict3_;
  std::map< std::string, void(&)(std::ostream &)> dict4_;
};
void executeCommand(std::ostream &out, std::istream &in, Commands &commands, dictOfDicts &dict, std::string command);
#endif
