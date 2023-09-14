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
  aksenov::makeDict(commands);
  std::string command = "";

  while(!std::cin.eof())
  {
    std::cin >> command;
    if (std::cin.eof())
    {
      break;
    }
    try
    {
      if (commands.find(command) != commands.end())
      {
        commands[command](std::cin, data);
      }
    }
    catch (const std::exception &e)
    {
      std::cin.setstate(std::istream::failbit);
      aksenov::outInvalidCommand(std::cout);
    }
    if(std::cin.fail())
    {
        aksenov::outInvalidCommand(std::cout);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
