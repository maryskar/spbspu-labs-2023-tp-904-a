#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <limits>
#include "polygon.h"
#include "commandMap.h"
bool getShapes(std::vector< aksenov::Polygon > &shapesArray, std::string fileName)
{
  std::ifstream in(fileName);
  if (!in.is_open())
  {
    std::cerr << "There was error opening file.";
    return false;
  }
  while (!in.eof())
  {
    std::copy(std::istream_iterator< aksenov::Polygon >(in), std::istream_iterator< aksenov::Polygon >(), std::back_inserter(shapesArray));
    if (in.fail() && !in.eof())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return true;
}

int main(int argc, char **argv)
{
  /*if (argc != 2)
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
  }*/
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
  /*while (inF >> polygon)
  {
    data.push_back(polygon);
  }*/
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
    if(std::cin.fail())
    {
        std::cout << "<INVALID COMMAND>" << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
