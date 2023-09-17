#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include "commands.h"
#include "polygonutils.h"
std::ostream &printError(std::ostream &out)
{
  return out << "<INVALID COMMAND>";
}
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "No file provided.\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Cannot open file.\n";
    return 1;
  }
  std::vector< romanovich::Polygon > polygons;
  using itType = std::istream_iterator< romanovich::Polygon >;
  while (!input.eof())
  {
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
    std::copy(itType(input), itType(), std::back_inserter(polygons));
  }
  romanovich::CommandProcessor commandProcessor;
  std::string command;
  while (std::getline(std::cin, command))
  {
    try
    {
      commandProcessor(command, polygons);
    }
    catch (...)
    {
      printError(std::cout) << "\n";
    }
  }
  return 0;
}
