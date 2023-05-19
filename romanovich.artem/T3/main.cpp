#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include "polygon.h"
#include "commands.h"
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
  size_t pointsCount;
  while (input >> pointsCount)
  {
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
    std::vector< romanovich::Point > points;
    for (size_t i = 0; i < pointsCount; i++)
    {
      romanovich::Point point{};
      input >> point;
      if (input.fail())
      {
        input.clear();
        input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        break;
      }
      points.push_back(point);
    }
    if (points.size() == pointsCount)
    {
      polygons.emplace_back(points);
    }
  }
  Commands commandProcessor;
  std::string command;
  while (std::getline(std::cin, command))
  {
    auto it = commandProcessor.commands.find(command);
    if (it != commandProcessor.commands.end())
    {
      (commandProcessor.*(it->second))(polygons);
    }
    else
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
  }
  return 0;
}
