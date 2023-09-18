#include <iostream>
#include "dictionaryOfCommands.hpp"

int main()
{
  dictionaryOfNames allDicts{};
  auto dictionary = DictionaryOfCommands();
  while (!std::cin.eof())
  {
    try
    {
      auto read = dictionary.readCommand(std::cin);
      dictionary.doCommand(read, dictionary, allDicts, std::cin, std::cout);
    }
    catch (const std::logic_error& e)
    {
      std::cout << "invalid command" << "\n";
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
