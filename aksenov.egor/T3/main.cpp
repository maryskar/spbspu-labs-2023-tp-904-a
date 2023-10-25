#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <stdexcept>
#include <limits>
#include "polygon.h"
#include "helpFunctions.h"
#include "commandMap.h"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Error" << "\n";
    return 1;
  }
  std::vector< aksenov::Polygon > data;
  if (!getShapes(data, argv[1]))
  {
    return 1;
  }
  aksenov::Polygon polygon;
  std::map< std::string, void (*)(std::istream&, const std::vector< aksenov::Polygon >&) > commands;
  commands = aksenov::makeDict();
  std::string command = "";

  while (!std::cin.eof())
  {
    std::cin >> command;
    if (std::cin.eof())
    {
      break;
    }
    try
    {
      commands.at(command)(std::cin, data);
    }
    catch (const std::logic_error &e)
    {
      aksenov::outInvalidCommand(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (...)
    {
      break;
    }
  }
  return 0;
}
