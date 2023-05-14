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
  for (const auto &polygon: polygons)
  {
    if (polygon.pointsCount() % 2 == (param == "EVEN"))
    {
      sum += polygon.getArea();
    }
  }
  std::cout << std::fixed << std::setprecision(1) << sum << '\n';
}
void executeCommand(Command::CommandList command, std::vector< Polygon > &polygons)
{
  if (command == Command::CommandList::AREA)
  {
    std::string param;
    std::cin >> param;
    if (param != "EVEN" && param != "ODD")
    {
      std::cerr << "<INVALID PARAMETER>\n";
    }
    else
    {
      areaCommand(polygons, param);
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
