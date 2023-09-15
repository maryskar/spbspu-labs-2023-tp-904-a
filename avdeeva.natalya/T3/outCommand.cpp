#include "outCommand.h"
#include <exception>
#include <map>
#include <string>
#include <functional>
#include "polygon.h"
#include "iofmtguard.h"
#include "commands.h"
void avdeeva::areaCommand(const std::deque< avdeeva::Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string argument;
  in >> argument;
  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }
  std::map< std::string, std::function< double(const std::deque< Polygon >) > > areaCommands(
    {
      {"EVEN", calcAreaEven},
      {"ODD", calcAreaOdd},
      {"MEAN", calcAreaMean}
    });
  double area = 0.0;
  try
  {
    area = areaCommands.at(argument)(polygons);
    avdeeva::iofmtguard guard(out);
    out << std::setprecision(1) << std::fixed << area << '\n';
  }
  catch (const std::exception & e)
  {
    size_t vertexes = std::stoull(argument);
    if (vertexes < 3)
    {
      throw std::logic_error("Polygons have more than 3 vertexes");
    }
    area = avdeeva::calcAreaVerts(polygons, vertexes);
    avdeeva::iofmtguard guard(out);
    out << std::setprecision(1) << std::fixed << area << '\n';
  }
}
void avdeeva::maxCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string argument;
  in >> argument;
  if (argument == "AREA")
  {
    avdeeva::iofmtguard guard(out);
    out << std::setprecision(1) << std::fixed << avdeeva::findMaxArea(polygons) << '\n';
  }
  else if (argument == "VERTEXES")
  {
    out << avdeeva::findMaxVerts(polygons) << '\n';
  }
  else
  {
    throw std::invalid_argument("Invalid command");
  }
}
void avdeeva::minCommand(const std::deque< avdeeva::Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string argument;
  in >> argument;
  if (argument == "AREA")
  {
    avdeeva::iofmtguard guard(out);
    out << std::setprecision(1) << std::fixed << avdeeva::findMinArea(polygons) << '\n';
  }
  else if (argument == "VERTEXES")
  {
    out << avdeeva::findMinVerts(polygons) << '\n';
  }
  else
  {
    throw std::invalid_argument("Invalid argument");
  }
}
void avdeeva::countCommand(const std::deque< avdeeva::Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string argument;
  in >> argument;
  if (!in)
  {
    throw std::runtime_error("Input error");
  }
  std::map< std::string, std::function< size_t(const std::deque< avdeeva:: Polygon >) > > countCommands(
    {
      {"EVEN", counterEven},
      {"ODD", counterOdd}
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
    count = avdeeva::counterVertexes(polygons, verts);
    out << count << '\n';
  }
}
void avdeeva::rightshapesCommand(const std::deque< avdeeva::Polygon > & polygons, std::istream & in, std::ostream & out)
{
  size_t count = avdeeva::countRightShapes(polygons);
  out << count << '\n';
}
void avdeeva::inframeCommand(const std::deque< avdeeva::Polygon > & polygons, std::istream & in, std::ostream & out)
{
  avdeeva::Polygon input;
  in >> input;
  if (!in)
  {
    throw std::runtime_error("Input error");
  }
  bool isInFrame = avdeeva::isInFrame(polygons, input);
  if (isInFrame)
  {
    out << "<TRUE>" << "\n";
  }
  else
  {
    out << "<FALSE>" << "\n";
  }
}