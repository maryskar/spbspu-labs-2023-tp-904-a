#include <fstream>
#include <iostream>
#include <iterator>
#include "Commands.h"
#include "FrequencyDictionary.h"

constexpr size_t MAX_STREAM_SIZE = std::numeric_limits< std::streamsize >::max();

int main()
{
  ganiullin::DictOfFreqDicts dicts;
  ganiullin::CommandHandler commandHandler{};

  while (!std::cin.eof()) {
    try {
      std::string command = commandHandler.readCommand(std::cin);
      commandHandler.execCommand(command, dicts, std::cin, std::cout);
    } catch (const std::logic_error& e) {
      std::cin.setstate(std::ios::failbit);
    } catch (const std::runtime_error& e) {
      break;
    }
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(MAX_STREAM_SIZE, '\n');
    }
    std::cout << '\n';
  }
  return 0;
}
