#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include "polygon.h"
#include "commandMap.h"
int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Error" << "\n";
    return 1;
  }
  std::ifstream inF;
  if (argc == 2)
  {
    inF.open(argv[1]);
    if (!inF.is_open())
    {
      std::cerr << "Error" << "\n";
      return 1;
    }
  }
  std::vector< aksenov::Polygon > data;
  using inputIterator = std::istream_iterator< aksenov::Polygon >;
  while (!inF.eof())
  {
    std::copy(inputIterator(inF), inputIterator(), std::back_inserter(data));
  }
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
    if (commands.find(command) != commands.end())
    {
      commands[command](std::cin, data);
    }
    else
    {
      std::cin.setstate(std::ios::failbit);
    }
  }
  return 0;
}
