#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <string>
#include <iomanip>
struct Command
{
  enum class CommandList
  {
    AREA,
    MAX,
    MIN,
    COUNT,
    MAXSEQ,
    RIGHTSHAPES
  };
};
void areaCommand(const std::vector< Polygon > &polygons, const std::string &param)
{
  double sum = 0;
  size_t count = 0;
  for (const auto &polygon: polygons)
  {
    if (param == "MEAN" || polygon.getPointsCount() % 2 == (param == "EVEN"))
    {
      sum += polygon.getArea();
      ++count;
    }
  }
  if (param == "MEAN")
  {
    sum /= count;
  }
  std::cout << std::fixed << std::setprecision(1) << sum << '\n';
}
void areaCommand(const std::vector< Polygon > &polygons, size_t verticesCount)
{
  double sum = 0;
  for (const auto &polygon: polygons)
  {
    if (polygon.getPointsCount() == verticesCount)
    {
      sum += polygon.getArea();
    }
  }
  std::cout << std::fixed << std::setprecision(1) << sum << '\n';
}
void executeCommand(const Command::CommandList &command, std::vector< Polygon > &polygons)
{
  if (command == Command::CommandList::AREA)
  {
    std::string param;
    std::cin >> param;
    if (param == "EVEN" || param == "ODD" || param == "MEAN")
    {
      areaCommand(polygons, param);
    }
    try
    {
      areaCommand(polygons, std::stoi(param));
    }
    catch (...)
    {
      std::cerr << "<INVALID PARAMETER>\n";
    }
  }
}
void processCommand(std::vector< Polygon > &polygons, const std::string &command)
{
  if (command == "AREA")
  {
    executeCommand(Command::CommandList::AREA, polygons);
  }
  else
  {
    std::cerr << "<INVALID COMMAND>\n";
  }
}
#endif
