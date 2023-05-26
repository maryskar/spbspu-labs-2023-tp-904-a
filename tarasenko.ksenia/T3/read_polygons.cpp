#include "read_polygons.h"
#include <string>
#include <iterator>

std::vector< tarasenko::Polygon > tarasenko::readPolygons(std::istream& in)
{
  std::vector< Polygon > polygons;
  while (in)
  {
    using in_iter = std::istream_iterator< Polygon >;
    while (!in.eof())
    {
      std::copy(in_iter(in), in_iter(), std::back_inserter(polygons));
      if (!in)
      {
        in.clear();
        std::string trash = "";
        std::getline(in, trash);
      }
    }
  }
  return polygons;
}
