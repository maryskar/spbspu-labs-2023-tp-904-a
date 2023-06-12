#include <iostream>
#include <iterator>
#include <fstream>
#include <functional>
#include <limits>
#include "polygon.h"
#include "commands.h"

int main(int argNum, char* argv[])
{
  if (argNum != 2)
  {
    std::cerr << "Error: wrong parameters number." << '\n';
    return 1;
  }
  std::cout << std::fixed;
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "Error: file could not be opened." << '\n';
    return 1;
  }
  constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
  std::vector< vagina::Polygon > polygon;
  while (!in.eof())
  {
    if (in.fail())
    {
      in.clear();
      in.ignore(max_size, '\n');
    }
    std::copy(std::istream_iterator< vagina::Polygon >(in),
      std::istream_iterator< vagina::Polygon >(),
      std::back_inserter(polygon));
  }
  in.close();
  auto read = std::bind(vagina::readCommand, std::ref(std::cin));
  auto commands = vagina::createDictionaryOfCommands();
  while (!std::cin.eof())
  {
    try
    {
      std::bind(vagina::doCommand, read, commands, polygon, std::ref(std::cin), std::ref(std::cout));
    }
    catch (const std::logic_error & e)
    {
      vagina::messageInvalidCommand(std::cout);
      std::cout << '\n';
      std::cin.ignore(max_size, '\n');
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
  }
  return 0;
}
