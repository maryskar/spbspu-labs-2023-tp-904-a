#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>

#include "Commands.h"
#include "FrequencyDictionary.h"
#include "NodeIO.h"
#include "TypesIO.h"

constexpr size_t MAX_SIZE = std::numeric_limits< std::streamsize >::max();

int main()
{
  ganiullin::Dicts dicts;
  ganiullin::CommandHandler commandHandler(std::cin, std::cout);

  while (!std::cin.eof()) {
    try {
      std::string command = commandHandler.readCommand();
      commandHandler.execCommand(command, dicts);
    } catch (const std::logic_error& e) {
      std::cin.setstate(std::ios::failbit);
    } catch (const std::runtime_error& e) {
      ganiullin::printErrorMessage(std::cout);
    }
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(MAX_SIZE, '\n');
    }
    std::cout << '\n';
  }
  return 0;
}
