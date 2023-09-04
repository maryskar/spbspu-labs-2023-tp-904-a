#include <iostream>
#include <iterator>
#include <fstream>
#include <functional>
#include <limits>
#include "commands.h"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cout << "error1";
    std::cout << "\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "error";
    return 1;
  }
  constexpr auto max = std::numeric_limits< std::streamsize >::max();
  std::vector< azheganova::Polygon > polygon;
  using ist_iter = std::istream_iterator< azheganova::Polygon >;
  while (!input.eof())
  {
    if (!input)
    {
      input.clear();
      input.ignore(max, '\n');
      std::copy(ist_iter(input), ist_iter(), std::back_inserter(polygon));
    }
  }
  azheganova::Commands commands;
  while (!std::cin.eof())
  {
    try
    {
      std::string input = azheganova::inputCommand(std::cin);
      azheganova::doCommand(input, commands, polygon, std::cin, std::cout);
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
    catch (const std::logic_error & e)
    {
      azheganova::printInvalidCommand(std::cout);
      std::cout << '\n';
      std::cin.ignore(max, '\n');
    }
  }
  return 0;
}
