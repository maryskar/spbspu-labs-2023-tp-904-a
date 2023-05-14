#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
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
namespace
{
  void maxCommand(const std::vector< Polygon > &polygons, const std::string &param)
  {
    if (polygons.empty())
    {
      std::cerr << "No polygons.\n";
      return;
    }
    if (param == "AREA")
    {
      const auto maxIt = std::max_element(polygons.begin(), polygons.end(), Polygon::AreaComp{});
      const auto i = std::distance(polygons.begin(), maxIt);
      std::cout << std::fixed << std::setprecision(1) << polygons[i].getArea() << '\n';
    }
    else if (param == "VERTEXES")
    {
      const auto maxIt = std::max_element(polygons.begin(), polygons.end(), Polygon::VertexCountComp{});
      const auto i = std::distance(polygons.begin(), maxIt);
      std::cout << polygons[i].getPointsCount() << '\n';
    }
  }
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
  else if (command == Command::CommandList::MAX)
  {
    std::string param;
    std::cin >> param;
    if (param == "AREA" || param == "VERTEXES")
    {
      maxCommand(polygons, param);
    }
    else
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
  else if (command == "MAX")
  {
    executeCommand(Command::CommandList::MAX, polygons);
  }
  else
  {
    std::cerr << "<INVALID COMMAND>\n";
  }
}
#endif
