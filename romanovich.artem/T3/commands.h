#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <string>
struct Command
{
  enum class CommandList
  {
    AREA_ODD,
    AREA_EVEN,
    AREA_MEAN,
    AREA,
    MAX,
    MIN,
    COUNT,
    MAXSEQ,
    RIGHTSHAPES
  };
};
std::string trim(const std::string &str)
{
  size_t first = str.find_first_not_of(' ');
  if (first == std::string::npos)
  {
    return "";
  }
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, last - first + 1);
}
void executeCommand(Command::CommandList command, const std::string &argument)
{
  if (command == Command::CommandList::COUNT)
  {
  }
}
void processCommand(const std::string &str)
{
  const char sep = ' ';
  int intBegin = 0;
  int intEnd = str.find(sep);
  std::string commandStr = str.substr(intBegin, intEnd - intBegin);
  std::string parametersLine = str.substr(intEnd - intBegin + 1);
  trim(parametersLine);
  for (size_t i = 0, j = 0; i != std::string::npos; i = j)
  {
    std::string argument = parametersLine.substr(i + (i != 0), (j = parametersLine.find(sep, i + 1)) - i - (i != 0));
    if (commandStr == "RIGHTSHAPES")
    {
      executeCommand(Command::CommandList::RIGHTSHAPES, argument);
    }
    else if (commandStr == "MAXSEQ")
    {
      executeCommand(Command::CommandList::MAXSEQ, argument);
    }
    else
    {
      std::cout << "Invalid command: " + commandStr + "\n";
    }
  }
}
#endif
