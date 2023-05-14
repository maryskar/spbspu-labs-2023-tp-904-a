#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>
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
  void rightShapesCountCommand(const std::vector< Polygon > &polygons)
  {
    size_t count = 0;
    for (const auto &polygon: polygons)
    {
      bool hasRightAngle = false;
      size_t n = polygon.getPointsCount();
      for (std::size_t i = 0; i < n; ++i)
      {
        const auto &pointA = polygon.getPoint(i);
        const auto &pointB = polygon.getPoint((i + 1) % n);
        const auto &pointC = polygon.getPoint((i + 2) % n);
        const auto v1 = pointB - pointA;
        const auto v2 = pointC - pointB;
        if (doScalarMultiplication(v1, v2) == 0)
        {
          hasRightAngle = true;
          break;
        }
      }
      if (hasRightAngle)
      {
        ++count;
      }
    }
    std::cout << count << '\n';
  }
  void maxSeqCommand(const std::vector< Polygon > &polygons, const Polygon &polygon)
  {
    if (polygons.empty())
    {
      std::cerr << "No polygons.\n";
      return;
    }
    auto not_comp = std::bind(std::negate<>(),
                              std::bind(Polygon::PolygonComparator(polygon), std::placeholders::_1,
                                        std::placeholders::_2));
    const auto maxSeq = std::adjacent_find(polygons.begin(), polygons.end(), not_comp);
    if (maxSeq == polygons.end())
    {
      std::cout << "0\n";
    }
    else
    {
      const auto start = maxSeq;
      const auto end = std::adjacent_find(maxSeq + 1, polygons.end(), not_comp);
      const auto count = end - start;
      std::cout << count << '\n';
    }
  }
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
  void countCommand(const std::vector< Polygon > &polygons, const std::string &param)
  {
    if (polygons.empty())
    {
      std::cerr << "No polygons.\n";
      return;
    }
    size_t count = 0;
    if (param == "EVEN")
    {
      count = std::count_if(polygons.begin(), polygons.end(), Polygon::IsEvenVertexCount{});
    }
    else if (param == "ODD")
    {
      count = std::count_if(polygons.begin(), polygons.end(), Polygon::IsOddVertexCount{});
    }
    std::cout << count << '\n';
  }
  void countCommand(const std::vector< Polygon > &polygons, size_t vertexCount)
  {
    if (polygons.empty())
    {
      std::cerr << "No polygons.\n";
      return;
    }
    size_t count = 0;
    try
    {
      count = std::count_if(polygons.begin(), polygons.end(), Polygon::HasVertexCount{vertexCount});
    }
    catch (...)
    {
      std::cerr << "Error: invalid parameter\n";
      return;
    }
    std::cout << count << '\n';
  }
  void minCommand(const std::vector< Polygon > &polygons, const std::string &param)
  {
    if (polygons.empty())
    {
      std::cerr << "No polygons.\n";
      return;
    }
    if (param == "AREA")
    {
      const auto maxIt = std::min_element(polygons.begin(), polygons.end(), Polygon::AreaComp{});
      const auto i = std::distance(polygons.begin(), maxIt);
      std::cout << std::fixed << std::setprecision(1) << polygons[i].getArea() << '\n';
    }
    else if (param == "VERTEXES")
    {
      const auto maxIt = std::min_element(polygons.begin(), polygons.end(), Polygon::VertexCountComp{});
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
    else
    {
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
  else if (command == Command::CommandList::MIN)
  {
    std::string param;
    std::cin >> param;
    if (param == "AREA" || param == "VERTEXES")
    {
      minCommand(polygons, param);
    }
    else
    {
      std::cerr << "<INVALID PARAMETER>\n";
    }
  }
  else if (command == Command::CommandList::COUNT)
  {
    std::string param;
    std::cin >> param;
    if (param == "EVEN" || param == "ODD")
    {
      countCommand(polygons, param);
    }
    else
    {
      try
      {
        countCommand(polygons, std::stoul(param));
      }
      catch (...)
      {
        std::cerr << "<INVALID PARAMETER>\n";
      }
    }
  }
  else if (command == Command::CommandList::RIGHTSHAPES)
  {
    rightShapesCountCommand(polygons);
  }
  else if (command == Command::CommandList::MAXSEQ)
  {
    try
    {
      std::vector< Point > points;
      size_t pointsCount;
      std::istream &input = std::cin;
      while (input >> pointsCount)
      {
        if (input.fail())
        {
          input.clear();
          input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
          continue;
        }
        for (size_t i = 0; i < pointsCount; i++)
        {
          Point point{};
          input >> point;
          if (input.fail())
          {
            input.clear();
            input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
            break;
          }
          points.push_back(point);
        }
        maxSeqCommand(polygons, Polygon(points));
      }
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
  else if (command == "MAX")
  {
    executeCommand(Command::CommandList::MAX, polygons);
  }
  else if (command == "MIN")
  {
    executeCommand(Command::CommandList::MIN, polygons);
  }
  else if (command == "COUNT")
  {
    executeCommand(Command::CommandList::COUNT, polygons);
  }
  else if (command == "MAXSEQ")
  {
    executeCommand(Command::CommandList::MAXSEQ, polygons);
  }
  else if (command == "RIGHTSHAPES")
  {
    executeCommand(Command::CommandList::RIGHTSHAPES, polygons);
  }
  else
  {
    std::cerr << "<INVALID COMMAND>\n";
  }
}
#endif
