#include <iostream>
#include <fstream>
#include <iterator>
#include <limits>
#include <stdexcept>

#include "dictionaryCommand.h"
#include "polygon.h"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Incorrect input" << '\n';
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "File not found" << '\n';
    return 1;
  }

  std::vector< aristarkhov::Polygon > polygons;

  while (!input.eof())
  {
    if (!input)
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(std::istream_iterator< aristarkhov::Polygon >(input),
        std::istream_iterator< aristarkhov::Polygon >(),
        std::back_inserter(polygons));
  }

  aristarkhov::Commands commandSystem;
  while (!std::cin.eof())
  {
    try
    {
      std::string command = aristarkhov::getCommand(std::cin);
      aristarkhov::doCommand(polygons, commandSystem, command, std::cout, std::cin);
    }
    catch (const std::logic_error& e)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cin.clear();
    }
    catch (const std::runtime_error& e)
    {
      break;
    }
  }
  return 0;
}
