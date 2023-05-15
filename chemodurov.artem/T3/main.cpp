#include <iostream>
#include <fstream>
#include <iterator>
#include <functional>
#include "read-and-do-command.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Not correct number of CML args\n";
    return 1;
  }
  std::ifstream ifstream(argv[1]);
  if (!ifstream.is_open())
  {
    std::cerr << "The file doesn't open\n";
    return 1;
  }

  std::vector< chemodurov::Polygon > data;
  while (!ifstream.eof())
  {
    if (ifstream.fail())
    {
      ifstream.clear();
      std::string line;
      std::getline(ifstream, line);
    }
    using is_it_t = std::istream_iterator< chemodurov::Polygon >;
    std::copy(is_it_t(ifstream), is_it_t(), std::back_inserter(data));
  }
  auto commands = chemodurov::createCommandDictionary();
  auto read = std::bind(chemodurov::readCommand, std::ref(std::cin));
  auto doComm = std::bind(chemodurov::doCommand, read, commands, data, std::ref(std::cin), std::ref(std::cout));
  do
  {
    try
    {
      doComm();
    }
    catch (const std::logic_error & e)
    {
      chemodurov::outInvalidCommand(std::cout);
      std::cout << '\n';
      std::string line;
      std::getline(std::cin, line);
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
  }
  while (!std::cin.eof());
  return 0;
}
