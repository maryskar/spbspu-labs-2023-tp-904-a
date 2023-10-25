#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <stdexcept>
#include <string>
#include "cleanStream.h"
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
  std::deque< mashkin::Polygon > polygons;
  using inpIter = std::istream_iterator< mashkin::Polygon >;
  while (!inpFile.eof())
  {
    std::copy(inpIter(inpFile), inpIter(), std::back_inserter(polygons));
    if (inpFile.fail())
    {
      mashkin::cleanStream(inpFile);
    }
  }
  std::map< std::string, std::ostream& (*)(std::istream&,
      std::ostream&,
      const std::deque< mashkin::Polygon >&) > commands;
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
        commands[command](std::cin, std::cout, polygons) << "\n";
      }
      else
      {
        throw std::logic_error("Command isn't found");
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
