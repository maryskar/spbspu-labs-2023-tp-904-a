#include "outCommand.h"
#include <iomanip>
#include <exception>
#include <map>
#include <string>
#include <functional>
#include "polygon.h"
#include "iofmtguard.h"
#include "commands.h"
void avdeeva::areaCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string argument;
  in >> argument;
  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }
  std::map< std::string, std::function< double (const std::deque< Polygon >) > > areaCommands(
    {
      {"EVEN", calcAreaEven},
      {"ODD",  calcAreaOdd},
      {"MEAN", calcAreaMean}
    });
  double area = 0.0;
  try
  {
    area = areaCommands.at(argument)(polygons);
    iofmtguard guard(out);
    out << std::setprecision(1) << std::fixed << area << '\n';
  }
  catch (const std::exception & e)
  {
    size_t vertexes = std::stoull(argument);
    if (vertexes < 3)
    {
      throw std::logic_error("Polygons have more than 3 vertexes");
    }
    area = calcAreaVerts(polygons, vertexes);
    iofmtguard guard(out);
    out << std::setprecision(1) << std::fixed << area << '\n';
  }
}
void avdeeva::maxCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string argument;
  in >> argument;
  if (argument == "AREA")
  {
    iofmtguard guard(out);
    out << std::setprecision(1) << std::fixed << findMaxArea(polygons) << '\n';
  }
  else if (argument == "VERTEXES")
  {
    out << findMaxVerts(polygons) << '\n';
  }
  else
  {
    throw std::invalid_argument("Invalid command");
  }
}
void avdeeva::minCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string argument;
  in >> argument;
  if (argument == "AREA")
  {
    iofmtguard guard(out);
    out << std::setprecision(1) << std::fixed << findMinArea(polygons) << '\n';
  }
  else if (argument == "VERTEXES")
  {
    out << findMinVerts(polygons) << '\n';
  }
  else
  {
    throw std::invalid_argument("Invalid argument");
  }
}
void avdeeva::countCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string argument;
  in >> argument;
  if (!in)
  {
    throw std::runtime_error("Input error");
  }
  std::map< std::string, std::function< size_t (const std::deque< Polygon >) > > countCommands
    ({
      {"EVEN", countEven},
      {"ODD", countOdd}
    });
  size_t count = 0;
  try
  {
    count = countCommands.at(argument)(polygons);
    out << count << '\n';
  }
  catch (const std::exception & e)
  {
    size_t verts = std::stoull(argument);
    if (verts < 3)
    {
      throw std::logic_error("Polygons have more than 3 vertexes");
    }
    count = countIsNumVertexes(polygons, verts);
    out << count << '\n';
  }
}
void avdeeva::rightshapesCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  if (in)
  {
    throw std::invalid_argument("Invalid argument");
  }
  size_t count = countRightShapes(polygons);
  out << count << '\n';
}
void avdeeva::inframeCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  Polygon input;
  in >> input;
  char check;
  if (!in || !(in.get(check) && check == '\n')))
  {
    throw std::runtime_error("Input error");
  }
  bool polInFrame = isInFrame(polygons, input);
  if (polInFrame)
  {
    out << "<TRUE>" << "\n";
  }
  else
  {
    out << "<FALSE>" << "\n";
  }
}
