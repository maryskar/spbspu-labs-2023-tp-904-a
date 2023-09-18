#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include "commands.h"
#include "commandsImpl.h"

int main()
{
  dictOfDicts dict;
  Commands commands;
  while (!std::cin.eof())
  {
    try
    {
      std::string command = insertCommand(std::cin);
      addHistory(command);
      executeCommand(std::cout, std::cin, commands, dict, command);
    }
    catch (...)
    {
      return 1;
    }
  }
}
