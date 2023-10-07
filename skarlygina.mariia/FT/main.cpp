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
  };

  std::map< std::string, const_command_t > const_commands
  {
    {"printWord", skarlygina::printWord},
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
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
  }
  return 0;
}