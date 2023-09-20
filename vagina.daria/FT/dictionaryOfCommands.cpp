#include "dictionaryOfCommands.hpp"

using DictionaryComm = vagina::DictionaryOfCommands;
DictionaryComm::DictionaryOfCommands()
{
  withoutOutput.insert({"createSet", createSet});
  withoutOutput.insert({"mergeDictionary", mergeDictionary});
  withoutOutput.insert({"uniqueWord", uniqueWord});
  constCommand.insert({"threeMostPopular", threeMostPopular});
  constCommand.insert({"findWord", findWord});
  constCommand.insert({"printWordToSpecificLetter", printWordToSpecificLetter});
  constCommand.insert({"printDictionary", printDictionary});
  constCommand.insert({"maxCountLetterDictionary", maxCountLetterDictionary});
  constCommand.insert({"minCountLetterDictionary", minCountLetterDictionary});
  constCommand.insert({"countIndentical", countIndentical});
  constCommand.insert({"wordsWithLetter", wordsWithLetter});
  notConstCommand.insert({"deleteWord", deleteWord});
}
void DictionaryComm::doCommWithoutOutput(const std::string& command, dictionaryOfNames& dict, std::istream& in) const
{
  auto func = withoutOutput.at(command);
  func(dict, in);
}
void DictionaryComm::doCommConstComm(const std::string& command,
  const dictionaryOfNames& dict, std::istream& in, std::ostream& out) const
{
  auto func = constCommand.at(command);
  func(dict, in, out);
}
void DictionaryComm::doCommNotConst(const std::string& command,
  dictionaryOfNames& dict, std::istream& in, std::ostream& out) const
{
  auto func = notConstCommand.at(command);
  func(dict, in, out);
}
std::string DictionaryComm::readCommand(std::istream& in)
{
  std::string comm = "";
  in >> comm;
  if (!in)
  {
    throw std::runtime_error("EOF");
  }
  return comm;
}
void DictionaryComm::doCommand(const std::string& command,
  const DictionaryOfCommands& commands, dictionaryOfNames& dest, std::istream& in, std::ostream& out)
{
  try
  {
    commands.doCommWithoutOutput(command, dest, in);
    return;
  }
  catch (const std::out_of_range& e)
  {}
  try
  {
    commands.doCommConstComm(command, dest, in, out);
    return;
  }
  catch (const std::out_of_range& e)
  {}
  try
  {
    commands.doCommNotConst(command, dest, in, out);
    return;
  }
  catch (const std::out_of_range& e)
  {}
}
