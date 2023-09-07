#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include "cleanStream.h"
#include "commands.h"
#include "mapWithCommands.h"
#include "polygon.h"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  std::ifstream inpFile;
  if (argc == 2)
  {
    inpFile.open(argv[1]);
    if (!inpFile.is_open())
    {
      std::cerr << "File isn't open\n";
      return 1;
    }
  }
  std::vector< mashkin::Polygon > res;
  using inpIter = std::istream_iterator< mashkin::Polygon >;
  while (!inpFile.eof())
  {
    std::copy(inpIter(inpFile), inpIter(), std::back_inserter(res));
    if (inpFile.fail())
    {
      mashkin::cleanStream(inpFile);
    }
  }
  std::map< std::string, void (*)(std::istream&, const std::vector< mashkin::Polygon >&) > commands;
  commands = mashkin::createMapWithCommands();
  std::string command;
  while (!std::cin.eof())
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
        commands[command](std::cin, res);
      }
      else
      {
        std::cin.setstate(std::ios::failbit);
      }
    }
    catch (const std::logic_error& ex)
    {
      std::cin.setstate(std::ios::failbit);
    }
    if (std::cin.fail())
    {
      std::cout << "<INVALID COMMAND>\n";
      mashkin::cleanStream(std::cin);
    }
  }
  return 0;
}
