/*#include <iostream>
#include <map>
#include <sstream>
#include "commands.h"

int main() {
  Commands commands;
  dict_t smallData;
  dictOfDicts data;
  while(!std::cin.eof())
  {
    try
    {
      std::string command = insertCommand(std::cin);
      std::string line = "";
      std::getline(std::cin, line);
      if (command == "translate")
      {
        executeCommand(std::cout, std::cin, commands, data, smallData, command, line);
      }
      else
      {
        line = "";
        executeCommand(std::cout, std::cin, commands, data, smallData, command, line);
      }
    }
    catch (const std::runtime_error &)
    {
      break;
    }
  }
}*/
#include <iostream>
#include <map>
#include <sstream>
#include <limits>
#include "commands.h"

int main() {
  Commands commands;
  dict_t smallData;
  dictOfDicts data;
  std::string line;

  while (std::getline(std::cin, line))
  {
    if (line.empty()) {
      continue; // Пропускаем пустые строки
    }

    std::string command;
    std::istringstream iss(line);
    iss >> command;

    if (command == "translate" || command == "createDictionary") {
      line = "";
      executeCommand(std::cout, iss, commands, data, smallData, command, line);
    } else {
      executeCommand(std::cout, iss, commands, data, smallData, command, line);
    }
  }
}
