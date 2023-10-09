#include <iostream>
#include <functional>
#include "commands.h"
#include "error_messages.h"

int main()
{
	using command_t = std::function< void(std::string&, skarlygina::Dicts_t&) >;
  using const_command_t = std::function< void(std::string&, const skarlygina::Dicts_t&) >;

  std::map< std::string, command_t > commands
  {
    {"analyze", skarlygina::analyze},
    {"deleteWord", skarlygina::deleteWord},
    {"merge", skarlygina::merge},
    {"rename", skarlygina::rename},
    {"intersect", skarlygina::intersect},
    {"deleteDict", skarlygina::deleteDict},
    {"complement", skarlygina::complement},
  };

  std::map< std::string, const_command_t > const_commands
  {
    {"printWord", skarlygina::printWord},
    {"printDict", skarlygina::printDict},
    {"writeInFile", skarlygina::writeInFile},
  };

  try
  {
    skarlygina::Dicts_t dicts;
    while (!std::cin.eof())
    {
      std::string command = "";
      std::cin >> command;
      if (command.empty())
      {
        continue;
      }
      auto iterator = commands.find(command);
      if (iterator != commands.end())
      {
        std::string str = "";
        std::getline(std::cin, str);
        iterator->second(str, dicts);
      }
      else
      {
        auto c_iterator = const_commands.find(command);
        if (c_iterator == const_commands.cend()) //!!!!!!!!!!!!
        {
          std::string temp = "";
          std::getline(std::cin, temp);
          skarlygina::errorInvalidCommandMessage(std::cerr);
          std::cout << "\n";
        }
        else
        {
          std::string str = "";
          std::getline(std::cin, str);
          c_iterator->second(str, dicts);
        }
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
  }
  return 0;
}
