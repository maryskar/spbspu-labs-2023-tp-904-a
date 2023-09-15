#include "outCommand.h"
#include <exception>
#include <map>
#include <string>
#include <functional>
#include "polygon.h"
#include "iofmtguard.h"
#include "commands.h"
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
    throw std::invalid_argument("Incorrect max parameter!");
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
    throw std::logic_error("Incorrect min argument!");
  }
}
void avdeeva::countCommand(const std::deque< avdeeva::Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string argument;
  in >> argument;
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