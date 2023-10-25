#include "commands.h"
#include <iomanip>
#include <string>
#include <algorithm>
#include <functional>
#include <map>
#include <iofmt_guard.h>
#include "help_commands.h"
#include "condition_template.h"

void skarlygina::getArea(const std::vector< Polygon >& polys, std::istream& in, std::ostream& out)
{
  std::map< std::string, std::function< double() > > commandArea = {
    {"EVEN", std::bind(findAreaEven, std::ref(polys))},
    {"ODD", std::bind(findAreaOdd, std::ref(polys))},
    {"MEAN", std::bind(findAreaMean, std::ref(polys))}
  };

  std::string command = "";
  in >> command;

  Iofmtguard guard(out);
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
    out << skarlygina::countNumOfVertexes(polys, num_vert) << '\n';
  }
}

void skarlygina::getMax(const std::vector< Polygon >& polys, std::istream& in, std::ostream& out)
{
  if (polys.empty())
  {
    throw std::invalid_argument("There are no polygons");
  }
  std::map < std::string, std::function < double() > > command_max =
  {
    {"AREA", std::bind(maxArea, std::ref(polys))},
    {"VERTEXES", std::bind(maxVertexes, std::ref(polys))}
  };
  std::string command = "";
  in >> command;
  Iofmtguard guard(out);
  out << std::fixed << (command == "AREA" ? std::setprecision(1) : std::setprecision(0));
  try
  {
    out << command_max.at(command)() << '\n';
  }
  catch (const std::out_of_range& e)
  {
    throw std::invalid_argument("False command");
  }
}

void skarlygina::getMin(const std::vector< Polygon >& polys, std::istream& in, std::ostream& out)
{
  if (polys.empty())
  {
    throw std::invalid_argument("There are no polygons");
  }
  std::map< std::string, std::function< double() > > command_min =
  {
    {"AREA", std::bind(minArea, std::ref(polys))},
    {"VERTEXES", std::bind(minVertexes, std::ref(polys))}
  };
  std::string command = "";
  in >> command;
  Iofmtguard guard(out);
  out << std::fixed << (command == "AREA" ? std::setprecision(1) : std::setprecision(0));
  try
  {
    out << command_min.at(command)() << '\n';
  }
  catch (const std::out_of_range& e)
  {
    throw std::invalid_argument("False command");
  }
}

void skarlygina::findPerms(const std::vector< Polygon >& polys, std::istream& in, std::ostream& out)
{
  skarlygina::Polygon base;
  in >> base;
  if (!in)
  {
    throw std::invalid_argument("False polygon");
  }
  out << std::count_if(polys.begin(), polys.end(), std::bind(&skarlygina::isPerm, base, std::placeholders::_1)) << '\n';
}

void skarlygina::findSame(const std::vector< Polygon >& polys, std::istream& in, std::ostream& out)
{
  skarlygina::Polygon poly;
  in >> poly;
  char check;
  if (!in || !(in.get(check) && check == '\n'))
  {
    throw std::logic_error("Invalid input");
  }
  auto same_dir = std::bind(isSame, std::placeholders::_1, poly);
  Iofmtguard iofmt(out);
  out << std::count_if(polys.begin(), polys.end(), same_dir) << '\n';
}

std::ostream& skarlygina::printInvalidCommand(std::ostream& out)
{
  return out << "<INVALID COMMAND>";
}
