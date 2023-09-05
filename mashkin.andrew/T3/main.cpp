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
  constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();
  std::map< std::string, void (*)(std::istream&, const std::vector< mashkin::Polygon >&) > commands;
  mashkin::createMapWithCommands(commands);
  std::string command;
  while (!std::cin.eof())
  {
    try
    {
      std::cin >> command;
      if (std::cin.eof())
      {
        break;
      }
      if (commands.find(command) != commands.end())
      {
        commands[command](std::cin, res);
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.setstate(std::ios::failbit);
      }
      if (std::cin.fail())
      {
        mashkin::cleanStream(std::cin);
      }
    }
    catch (const std::exception& ex)
    {
      std::cin.ignore(maxSize, '\n');
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  return 0;
}
