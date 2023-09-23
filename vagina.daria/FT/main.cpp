#include <iostream>
#include "dictionaryOfCommands.hpp"
#include <commands.h>

int main()
{
  vagina::dictionaryOfNames allDicts{};
  auto dictionary = vagina::DictionaryOfCommands();
  while (!std::cin.eof())
  {
    try
    {
      auto read = dictionary.readCommand(std::cin);
      dictionary.doCommand(read, dictionary, allDicts, std::cin, std::cout);
    }
    catch (const std::invalid_argument& e)
    {
      vagina::messageEmptyCommand(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error& e)
    {
      vagina::messageInvalidCommand(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::runtime_error& e)
    {
      break;
    }
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
