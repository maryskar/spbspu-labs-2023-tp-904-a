#include "commands.h"
#include <iomanip>
#include <string>
#include <algorithm>
#include <functional>
#include <map>
#include <iofmt_guard.h>
#include "help_commands.h"

void skarlygina::getArea(const std::vector< Polygon >& polys, std::istream& in, std::ostream& out)
{
  std::map< std::string, std::function< double() > > commandArea = {
    {"EVEN", std::bind(findAreaEven, std::ref(polys))},
    {"ODD", std::bind(findAreaOdd, std::ref(polys))},
    {"MEAN", std::bind(findAreaMean, std::ref(polys))}
  };

  std::string command = "";
  in >> command;

  iofmtguard guard(out);
  out << std::fixed << std::setprecision(1);
  try
  {
    out << commandArea.at(command)() << '\n';
  }
  catch (const std::out_of_range&)
  {
    size_t number_vert = std::stoul(command);
    out << findAreaNumOfVertexes(polys, number_vert) << '\n';
  }
}
void skarlygina::countFigures(const std::vector< Polygon >& polys, std::istream& in, std::ostream& out)
{
  std::map< std::string, std::function< size_t() > > command_count = {
    {"ODD", std::bind(countOdd, std::ref(polys))},
    {"EVEN", std::bind(countEven, std::ref(polys))}
  };
  std::string command = "";
  in >> command;
  try
  {
    out << command_count.at(command)() << '\n';
  }
  catch (const std::out_of_range&)
  {
    size_t num_vert = std::stoul(command);
    out << countNumOfVertexes(polys, num_vert) << '\n';
  }
}

void skarlygina::getMax(const std::vector< Polygon >& polys, std::istream& in, std::ostream& out)
{
  if (polys.empty()) {
    throw std::invalid_argument("There are no polygons");
  }
  std::string command = "";
  in >> command;
  iofmtguard guard(out);
  out << std::fixed << std::setprecision(1);
  if (command == "AREA")
  {
    out << maxArea(polys) << '\n';
  }
  else if (command == "VERTEXES")
  {
    out << maxVertexes(polys) << '\n';
  }
  else
  {
    throw std::invalid_argument("False command");
  }
}

void skarlygina::getMin(const std::vector< Polygon >& polys, std::istream& in, std::ostream& out)
{
  std::string command = "";
  in >> command;
  iofmtguard guard(out);
  out << std::fixed << std::setprecision(1);
  if (command == "AREA")
  {
    out << minArea(polys) << '\n';
  }
  else if (command == "VERTEXES")
  {
    out << minVertexes(polys) << '\n';
  }
  else
  {
    throw std::invalid_argument("Unknown command");
  }
}

void skarlygina::findPerms(const std::vector< Polygon >& polys, std::istream& in, std::ostream& out)
{
  skarlygina::Polygon base;
  in >> base;
  if (!in)
  {
    throw std::invalid_argument("");
  }
  out << std::count_if(polys.begin(), polys.end(), std::bind(&skarlygina::findPerms, base, std::placeholders::_1)) << '\n';
}

void skarlygina::findSame(const std::vector< Polygon >& polys, std::istream& in, std::ostream& out)
{
  skarlygina::Polygon polygon_first;
  in >> polygon_first;
  if (in.rdstate() == std::ios::failbit)
  {
    throw std::invalid_argument("Incorrect enter shape");
  }
  auto check_same = std::bind(isSame, std::placeholders::_1, polygon_first);
  out << std::count_if(polys.begin(), polys.end(), check_same) << '\n';
}

std::ostream& skarlygina::printInvalidCommand(std::ostream& out)
{
  return out << "<INVALID COMMAND>\n";
}
