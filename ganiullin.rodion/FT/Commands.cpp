#include "Commands.h"

#include <fstream>
#include <iostream>
#include <limits>

#include "TypesIO.h"

namespace {
  constexpr size_t MAX_SIZE = std::numeric_limits< std::streamsize >::max();

  using Dicts = ganiullin::Dicts;
  using NodeType = std::pair< std::string, size_t >;
  using SubComm = ganiullin::SubComm;
  using SubCommDict = ganiullin::SubCommDict;
  using FreqDict = ganiullin::FreqDict;

  size_t plusFunc(const size_t& lhs, const size_t& rhs)
  {
    return lhs + rhs;
  }
  size_t minusFunc(const size_t& lhs, const size_t& rhs)
  {
    return lhs - rhs;
  }
  size_t minFunc(const size_t& lhs, const size_t& rhs)
  {
    return std::min(lhs, rhs);
  }
  size_t maxFunc(const size_t& lhs, const size_t& rhs)
  {
    return std::max(lhs, rhs);
  }
  size_t firstFunc(const size_t& lhs, const size_t& rhs)
  {
    return lhs;
  }
}
using CommHand = ganiullin::CommandHandler;

void CommHand::help()
{
  comOut_ << "1) help";
  comOut_ << " - Выводит этот список команд с небольшим пояснением" << '\n';
  comOut_ << "2) load <file>";
  comOut_ << " - читает словари из файла ";
  comOut_ << "(словарь в формате <dictName> key1 value1 key2 value2)" << '\n';
  comOut_ << "3) save <file> <dicts>";
  comOut_ << " - записывает словари в файл в приведенном выше формате" << '\n';
  comOut_ << "4) print <dict>";
  comOut_ << " - выводит отсортированный по значению словарь. ";
  comOut_ << "Все слова переводятся в нижний регистр" << '\n';
  comOut_ << "5) union <command> <dict1> <dict2> <dict3>";
  comOut_ << " - создает словарь dict3 с OR двух словарей*" << '\n';
  comOut_ << "6) intersection <command> <dict1> <dict2> <dict3>";
  comOut_ << " - создает словарь dict3 с AND двух словарей*" << '\n';
  comOut_ << "7) diff <dict1> <dict2> <dict3>";
  comOut_ << " - создает словарь dict3 с XOR двух словарей" << '\n';
  comOut_ << "8) read <file> <dict>";
  comOut_ << " - читает текст из файла ";
  comOut_ << "и считает частоту встречаемости слов" << '\n';
  comOut_ << "9) common <dict> <num>";
  comOut_ << " - выводит на экран топ <num> самых частых слов" << '\n';
  comOut_ << "10) rare <dict> <num>";
  comOut_ << " - выводит на экран топ <num> самых редких слов" << '\n';
  comOut_ << "11) get <dict> <key> - выводит пару ключ : значение" << '\n';
  comOut_ << "12) dicts";
  comOut_ << " - выводит список созданных словарей" << '\n';
  comOut_ << "* <command>";
  comOut_ << " при дубликатах ключей используется указанная команда" << '\n';
  comOut_ << "  PLUS - сумма значений" << '\n';
  comOut_ << "  MINUS - разность" << '\n';
  comOut_ << "  MIN - минимальное из значений" << '\n';
  comOut_ << "  MAX - максимальное из значений" << '\n';
  comOut_ << "  FIRST - берет значение из первого словаря";
}

void CommHand::listDicts(const Dicts& dicts)
{
  size_t i = 0;
  for (const std::pair< std::string, FreqDict >& elem : dicts) {
    comOut_ << elem.first;
    ++i;
    if (i != dicts.size()) {
      comOut_ << ' ';
    }
  }
  if (dicts.size() == 0) {
    comOut_ << "No dicts";
  }
}
void CommHand::printDict(const Dicts& dicts)
{
  std::string dictName;
  comIn_ >> dictName;

  if (dicts.find(dictName) == std::end(dicts)) {
    comOut_ << "No such dict " << dictName;
  }
  comOut_ << dicts.find(dictName)->second;
}
void CommHand::printCommon(const Dicts& dicts)
{
  std::string dictName;
  size_t num = 0;
  comIn_ >> dictName >> num;
  if (dicts.find(dictName) == std::end(dicts)) {
    comOut_ << "No such dict " << dictName;
  } else {
    dicts.find(dictName)->second.printCommonElems(comOut_, num);
  }
}
void CommHand::printRare(const Dicts& dicts)
{
  std::string dictName;
  size_t num = 0;
  comIn_ >> dictName >> num;
  if (dicts.find(dictName) == std::end(dicts)) {
    comOut_ << "No such dict " << dictName;
  } else {
    dicts.find(dictName)->second.printRareElems(comOut_, num);
  }
}
void CommHand::printElem(const Dicts& dicts)
{
  std::string dictName;
  ganiullin::Word word("");
  comIn_ >> dictName >> word;
  auto dictIt = dicts.find(dictName);
  if (dictIt == std::end(dicts)) {
    comOut_ << "No such dict " << dictName;
  } else if (!dictIt->second.contains(word)) {
    comOut_ << "No such word " << word << " in dict " << dictName;
  } else {
    comOut_ << word << ' ' << dictIt->second.at(word);
  }
}
void CommHand::getUnion(Dicts& dicts)
{
  std::string command;
  std::string lhs;
  std::string rhs;
  std::string dictName;
  comIn_ >> command >> lhs >> rhs >> dictName;

  if (subCommandDict_.find(command) == std::end(subCommandDict_)) {
    comOut_ << "Unknown command " << command;
    return;
  } else if (dicts.find(lhs) == std::end(dicts)) {
    comOut_ << "No such dict " << lhs;
    return;
  } else if (dicts.find(rhs) == std::end(dicts)) {
    comOut_ << "No such dict " << rhs;
    return;
  } else {
    const FreqDict& lhsDict = dicts.find(lhs)->second;
    const FreqDict& rhsDict = dicts.find(rhs)->second;
    const SubComm& subComm = subCommandDict_.find(command)->second;

    dicts[dictName] = lhsDict.merge(rhsDict, subComm);
    comOut_ << dictName;
  }
}
void CommHand::getIntersection(Dicts& dicts)
{
  std::string command;
  std::string lhs;
  std::string rhs;
  std::string dictName;
  comIn_ >> command >> lhs >> rhs >> dictName;

  if (subCommandDict_.find(command) == std::end(subCommandDict_)) {
    comOut_ << "Unknown command " << command;
    return;
  } else if (dicts.find(lhs) == std::end(dicts)) {
    comOut_ << "No such dict " << lhs;
    return;
  } else if (dicts.find(rhs) == std::end(dicts)) {
    comOut_ << "No such dict " << rhs;
    return;
  } else {
    const FreqDict& lhsDict = dicts.find(lhs)->second;
    const FreqDict& rhsDict = dicts.find(rhs)->second;
    const SubComm& subComm = subCommandDict_.find(command)->second;

    dicts[dictName] = lhsDict.intersect(rhsDict, subComm);
    comOut_ << dictName;
  }
}
void CommHand::getDiff(Dicts& dicts)
{
  std::string lhs;
  std::string rhs;
  std::string dictName;
  comIn_ >> lhs >> rhs >> dictName;

  if (dicts.find(lhs) == std::end(dicts)) {
    comOut_ << "No such dict " << lhs;
    return;
  } else if (dicts.find(rhs) == std::end(dicts)) {
    comOut_ << "No such dict " << rhs;
    return;
  } else {
    const FreqDict& lhsDict = dicts.find(lhs)->second;
    const FreqDict& rhsDict = dicts.find(rhs)->second;
    dicts[dictName] = lhsDict.diff(rhsDict);
    comOut_ << dictName;
  }
}

void CommHand::loadDicts(Dicts& dicts)
{
  using del = ganiullin::DelimiterIO;
  std::string filename;
  comIn_ >> filename;
  std::ifstream file(filename);

  if (!file.is_open()) {
    comOut_ << "Could not open a file " << filename;
    return;
  }
  while (!file.eof()) {
    std::string dictName;
    file >> dictName;
    if (dictName.size() != 0) {
      file >> dicts[dictName];
    }
    if (!file) {
      file.clear();
      file.ignore(MAX_SIZE, '\n');
    }
  }
  file.close();
  comOut_ << "File " << filename << " successfully loaded";
}
void CommHand::readIntoDict(Dicts& dicts)
{
  std::string filename;
  std::string dictName;
  comIn_ >> filename >> dictName;
  std::ifstream file(filename);

  if (!file.is_open()) {
    comOut_ << "Could not open a file " << filename;
    return;
  }
  dicts[dictName].readText(file);
  file.close();
  comOut_ << "File " << filename << " successfully loaded";
}
void CommHand::saveDicts(const Dicts& dicts)
{
  std::string filename;
  comIn_ >> filename;
  std::ofstream file(filename);

  if (!file.is_open()) {
    comOut_ << "Could not open a file " << filename;
    return;
  }
  while (comIn_.peek() != '\n') {
    std::string dictName;
    comIn_ >> dictName;
    if (dicts.find(dictName) == std::end(dicts)) {
      comOut_ << "No such dict " << dictName << '\n';
    }
    file << dictName << ' ';
    file << dicts.find(dictName)->second;
    file << '\n';
  }
  file.close();
  comOut_ << "File " << filename << " successfully loaded";
}

CommHand::CommandHandler(std::istream& in, std::ostream& out)
    : infoFuncDict_()
    , constFuncDict_()
    , nonConstFuncDict_()
    , subCommandDict_()
    , comIn_(in)
    , comOut_(out)
{

  infoFuncDict_["help"] = &CommandHandler::help;

  constFuncDict_["dicts"] = &CommandHandler::listDicts;
  constFuncDict_["print"] = &CommandHandler::printDict;
  constFuncDict_["print"] = &CommandHandler::printDict;
  constFuncDict_["common"] = &CommandHandler::printCommon;
  constFuncDict_["rare"] = &CommandHandler::printRare;
  constFuncDict_["get"] = &CommandHandler::printElem;
  constFuncDict_["save"] = &CommandHandler::saveDicts;

  nonConstFuncDict_["union"] = &CommandHandler::getUnion;
  nonConstFuncDict_["intersection"] = &CommandHandler::getIntersection;
  nonConstFuncDict_["diff"] = &CommandHandler::getDiff;
  nonConstFuncDict_["load"] = &CommandHandler::loadDicts;
  nonConstFuncDict_["read"] = &CommandHandler::readIntoDict;

  subCommandDict_.reserve(5);
  subCommandDict_["PLUS"] = &plusFunc;
  subCommandDict_["MINUS"] = &minusFunc;
  subCommandDict_["MIN"] = &minFunc;
  subCommandDict_["MAX"] = &maxFunc;
  subCommandDict_["FIRST"] = &firstFunc;
}
std::string CommHand::readCommand() const
{
  std::string command;
  comIn_ >> command;
  if (!comIn_) {
    throw std::runtime_error("Failed to read command");
  }
  return command;
}
std::ostream& CommHand::execCommand(const std::string& command, Dicts& dicts)
{
  if (infoFuncDict_.find(command) != std::end(infoFuncDict_)) {
    (this->*(infoFuncDict_.at(command)))();
  } else if (constFuncDict_.find(command) != std::end(constFuncDict_)) {
    (this->*(constFuncDict_.at(command)))(dicts);
  } else if (nonConstFuncDict_.find(command) != std::end(nonConstFuncDict_)) {
    (this->*(nonConstFuncDict_.at(command)))(dicts);
  } else {
    throw std::runtime_error("Unknown command");
  }
  return comOut_;
}
