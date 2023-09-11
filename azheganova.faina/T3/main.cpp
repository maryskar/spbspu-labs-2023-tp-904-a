#include <iostream>
#include <iterator>
#include <fstream>
#include <functional>
#include <limits>
#include <numeric>
#include <string>
#include <map>
#include "commands.h"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cout << "error";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cout << "error";
    return 1;
  }
  std::vector< azheganova::Polygon > polygon;
  using ist_iter = std::istream_iterator< azheganova::Polygon >;
  while (!input.eof())
  {
    std::copy(ist_iter(input), ist_iter(), std::back_inserter(polygon));
    if (!input)
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
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
    catch (const std::logic_error & e)
    {
      azheganova::printInvalidCommand(std::cout);
      std::cout << '\n';
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cin.clear();
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
  }
  return 0;
}

