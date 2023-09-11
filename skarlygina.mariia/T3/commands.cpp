#include "commands.h"
#include <iomanip>
#include <string>
#include <algorithm>
#include <functional>
#include <map>
#include <iofmt_guard.h>
#include "help_commands.h"

void skarlygina::getArea(const std::vector< Polygon >& polys, std::istream& in, std::ostream& out);
void skarlygina::countFigures(const std::vector< Polygon >&, std::istream&, std::ostream&);
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

void skarlygina::findSame(const std::vector< Polygon >&, std::istream&, std::ostream&);
std::ostream& skarlygina::printInvalidCommand(std::ostream&);
