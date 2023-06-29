#include "Commands.h"

#include <fstream>
#include <iostream>
#include "TypesIO.h"

namespace {
  using DictOfFreqDicts = ganiullin::DictOfFreqDicts;
  using NodeType = ganiullin::NodeType;
  using SubCommand = ganiullin::SubCommand;
  using SubCommandDict = ganiullin::SubCommandDict;
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
  std::ostream& help(std::ostream& out)
  {
    out << "1) help - Выводит этот список команд с небольшим пояснением" << '\n';
    out << "2) load <file> - читает словари из файла";
    out << "(словарь в формате <dictName> key1 value1 key2 value2)" << '\n';
    out << "3) save <file> <dicts> - записывает словари в файл в приведенном выше формате" << '\n';
    out << "4) print <dict> - выводит отсортированный по значению словарь. ";
    out << "Все слова переводятся в нижний регистр" << '\n';
    out << "5) union <command> <dict1> <dict2> <dict3> - создает словарь dict3 с OR двух словарей*"
        << '\n';
    out << "6) intersection <command> <dict1> <dict2> <dict3>";
    out << " - создает словарь dict3 с AND двух словарей*" << '\n';
    out << "7) diff <dict1> <dict2> <dict3> - создает словарь dict3 с XOR двух словарей" << '\n';
    out << "8) read <file> <dict> - читает текст из файла и считает частоту встречаемости слов"
        << '\n';
    out << "9) common <dict> <num> - выводит на экран топ <num> самых частых слов" << '\n';
    out << "10) rare <dict> <num> - выводит на экран топ <num> самых редких слов" << '\n';
    out << "11) get <dict> <key> - выводит пару ключ : значение" << '\n';
    out << "12) dicts - выводит список созданных словарей" << '\n';
    out << "* <command> при дубликатах ключей используется указанная команда" << '\n';
    out << "  PLUS - сумма значений" << '\n';
    out << "  MINUS - разность" << '\n';
    out << "  MIN - минимальное из значений" << '\n';
    out << "  MAX - максимальное из значений" << '\n';
    out << "  FIRST - берет значение из первого словаря";
    return out;
  }
  std::ostream& listDicts(const DictOfFreqDicts& dicts, std::ostream& out)
  {
    for (const std::pair< std::string, FreqDict >& elem : dicts) {
      out << elem.first << ' ';
    }
    return out;
  }
  std::ostream& printDict(const DictOfFreqDicts& dicts, std::istream& in, std::ostream& out)
  {
    std::string dictName;
    in >> dictName;

    if (dicts.find(dictName) == std::end(dicts)) {
      out << "No such dict " << dictName;
    }
    ganiullin::print(out, dicts.find(dictName)->second);
    return out;
  }
  std::ostream& printCommon(const DictOfFreqDicts& dicts, std::istream& in, std::ostream& out)
  {
    std::string dictName;
    size_t num;
    in >> dictName >> num;
    if (dicts.find(dictName) == std::end(dicts)) {
      out << "No such dict " << dictName;
    } else {
      ganiullin::printCommonElems(out, dicts.find(dictName)->second, num);
    }
    return out;
  }
  std::ostream& printRare(const DictOfFreqDicts& dicts, std::istream& in, std::ostream& out)
  {
    std::string dictName;
    size_t num;
    in >> dictName >> num;
    if (dicts.find(dictName) == std::end(dicts)) {
      out << "No such dict " << dictName;
    } else {
      ganiullin::printRareElems(out, dicts.find(dictName)->second, num);
    }
    return out;
  }
  std::ostream& printElem(const DictOfFreqDicts& dicts, std::istream& in, std::ostream& out)
  {
    std::string dictName;
    std::string word;
    in >> dictName >> word;
    auto dictIt = dicts.find(dictName);
    if (dictIt == std::end(dicts)) {
      out << "No such dict " << dictName;
    } else if (dictIt->second.find(word) == std::end(dictIt->second)) {
      out << "No such word " << word << " in dict " << dictName;
    } else {
      NodeType node = *(dictIt->second.find(word));
      out << node.first << ' ' << node.second;
    }
    return out;
  }
  void getUnion(DictOfFreqDicts& dicts, const SubCommandDict& subCommDict, std::istream& in,
      std::ostream& out)
  {
    std::string command;
    std::string lhs;
    std::string rhs;
    std::string dictName;
    in >> command >> lhs >> rhs >> dictName;

    if (subCommDict.find(command) == std::end(subCommDict)) {
      out << "Unknown command " << command;
      return;
    } else if (dicts.find(lhs) == std::end(dicts)) {
      out << "No such dict " << lhs;
      return;
    } else if (dicts.find(rhs) == std::end(dicts)) {
      out << "No such dict " << rhs;
      return;
    } else {
      const FreqDict& lhsDict = dicts.find(lhs)->second;
      const FreqDict& rhsDict = dicts.find(rhs)->second;
      const SubCommand& subComm = subCommDict.find(command)->second;

      dicts[dictName] = ganiullin::merge(lhsDict, rhsDict, subComm);
    }
  }
  void getIntersection(DictOfFreqDicts& dicts, const SubCommandDict& subCommDict, std::istream& in,
      std::ostream& out)
  {
    std::string command;
    std::string lhs;
    std::string rhs;
    std::string dictName;
    in >> command >> lhs >> rhs >> dictName;

    if (subCommDict.find(command) == std::end(subCommDict)) {
      out << "Unknown command " << command;
      return;
    } else if (dicts.find(lhs) == std::end(dicts)) {
      out << "No such dict " << lhs;
      return;
    } else if (dicts.find(rhs) == std::end(dicts)) {
      out << "No such dict " << rhs;
      return;
    } else {
      const FreqDict& lhsDict = dicts.find(lhs)->second;
      const FreqDict& rhsDict = dicts.find(rhs)->second;
      const SubCommand& subComm = subCommDict.find(command)->second;

      dicts[dictName] = ganiullin::getIntersect(lhsDict, rhsDict, subComm);
    }
  }
  void getDiff(DictOfFreqDicts& dicts, std::istream& in, std::ostream& out)
  {
    std::string lhs;
    std::string rhs;
    std::string dictName;
    in >> lhs >> rhs >> dictName;

    if (dicts.find(lhs) == std::end(dicts)) {
      out << "No such dict " << lhs;
      return;
    } else if (dicts.find(rhs) == std::end(dicts)) {
      out << "No such dict " << rhs;
      return;
    } else {
      const FreqDict& lhsDict = dicts.find(lhs)->second;
      const FreqDict& rhsDict = dicts.find(rhs)->second;
      dicts[dictName] = ganiullin::getDifference(lhsDict, rhsDict);
    }
  }
}
void loadDicts(DictOfFreqDicts& dicts, std::istream& in, std::ostream& out)
{
  using del = ganiullin::DelimiterIO;
  std::string filename;
  in >> filename;
  std::ifstream file(filename);

  if (!file.is_open()) {
    out << "Could not open a file " << filename;
    return;
  }
  while (!file.eof()) {
    std::string dictName;
    file >> dictName;
    ganiullin::loadDict(file, dicts[dictName]);
  }
  out << "File " << filename << " successfully loaded";
}
void readIntoDict(DictOfFreqDicts& dicts, std::istream& in, std::ostream& out)
{
  std::string filename;
  std::string dictName;
  in >> filename >> dictName;
  std::ifstream file(filename);

  if (!file.is_open()) {
    out << "Could not open a file " << filename;
    return;
  }
  ganiullin::readText(file, dicts[dictName]);
  out << "dict successfully loaded";
}
void saveDicts(const DictOfFreqDicts& dicts, std::istream& in, std::ostream& out)
{
  std::string filename;
  in >> filename;
  std::ofstream file(filename);

  if (!file.is_open()) {
    out << "Could not open a file " << filename;
    return;
  }
  while (in.peek() != '\n') {
    std::string dictName;
    in >> dictName;
    if (dicts.find(dictName) == std::end(dicts)) {
      out << "No such dict " << dictName << '\n';
    }
    file << dictName << ' ';
    ganiullin::saveDict(file, dicts.find(dictName)->second);
  }
  out << "dicts successfully saved";
}

ganiullin::CommandHandler::CommandHandler():
  infoFuncDict_(),
  stateFuncDict_(),
  printFuncDict_(),
  funcWithSubDict_(),
  inFileFuncDict_(),
  outFileFuncDict_(),
  funcNoSubDict_(),
  subCommandDict_()
{
  infoFuncDict_["help"] = &help;

  stateFuncDict_["dicts"] = &listDicts;

  printFuncDict_.reserve(4);
  printFuncDict_["print"] = &printDict;
  printFuncDict_["common"] = &printCommon;
  printFuncDict_["rare"] = &printRare;
  printFuncDict_["get"] = &printElem;

  funcWithSubDict_.reserve(2);
  funcWithSubDict_["union"] = &getUnion;
  funcWithSubDict_["intersection"] = &getIntersection;

  funcNoSubDict_["diff"] = &getDiff;

  inFileFuncDict_.reserve(2);
  inFileFuncDict_["load"] = &loadDicts;
  inFileFuncDict_["read"] = &readIntoDict;

  outFileFuncDict_["save"] = &saveDicts;

  subCommandDict_.reserve(5);
  subCommandDict_["PLUS"] = &plusFunc;
  subCommandDict_["MINUS"] = &minusFunc;
  subCommandDict_["MIN"] = &minFunc;
  subCommandDict_["MAX"] = &maxFunc;
  subCommandDict_["FIRST"] = &firstFunc;
}
std::string ganiullin::CommandHandler::readCommand(std::istream& in) const
{
  std::string command;
  in >> command;
  if (!in) {
    throw std::runtime_error("Failed to read command");
  }
  return command;
}
std::ostream& ganiullin::CommandHandler::execCommand(const std::string& command,
    DictOfFreqDicts& dicts, std::istream& in, std::ostream& out) const
{
  if (infoFuncDict_.find(command) != std::end(infoFuncDict_)) {
    infoFuncDict_.find(command)->second(out);
  } else if (stateFuncDict_.find(command) != std::end(stateFuncDict_)) {
    stateFuncDict_.find(command)->second(dicts, out);
  } else if (printFuncDict_.find(command) != std::end(printFuncDict_)) {
    printFuncDict_.find(command)->second(dicts, in, out);
  } else if (funcWithSubDict_.find(command) != std::end(funcWithSubDict_)) {
    funcWithSubDict_.find(command)->second(dicts, subCommandDict_, in, out);
  } else if (outFileFuncDict_.find(command) != std::end(outFileFuncDict_)) {
    outFileFuncDict_.find(command)->second(dicts, in, out);
  } else if (inFileFuncDict_.find(command) != std::end(inFileFuncDict_)) {
    inFileFuncDict_.find(command)->second(dicts, in, out);
  } else if (funcNoSubDict_.find(command) != std::end(funcNoSubDict_)) {
    funcNoSubDict_.find(command)->second(dicts, in, out);
  } else {
    out << "Unknown command";
  }
  return out;
}
