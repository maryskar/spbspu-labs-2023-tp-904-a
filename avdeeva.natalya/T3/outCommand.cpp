#include "outCommand.h"
#include "commands.h"
void avdeeva::rightshapesCommand(const std::deque< avdeeva::Polygon >& polygons, std::istream& in, std::ostream& out)
{
  if (!in)
  {
    throw std::invalid_argument("Incorrect parameter");
  }
  size_t count = avdeeva::countRightShapes(polygons);
  out << count << '\n';
}
void avdeeva::inframeCommand(const std::deque< avdeeva::Polygon > & polygons, std::istream & in, std::ostream & out)
{
  avdeeva::Polygon input;
  in >> input;
  if (!in)
  {
    throw std::invalid_argument("Incorrect parameter");
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