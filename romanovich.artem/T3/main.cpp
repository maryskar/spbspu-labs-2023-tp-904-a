#include <fstream>
#include <iostream>
#include <limits>
#include "commands.h"
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
      romanovich::Point point{0, 0};
      input >> point;
      if (input.fail())
      {
        input.clear();
        input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        break;
      }
      if (std::find(points.begin(), points.end(), point) != points.end())
      {
        continue;
      }
      points.push_back(point);
    }
    if (points.size() == pointsCount && points.size() > 2)
    {
      polygons.emplace_back(points);
    }
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
