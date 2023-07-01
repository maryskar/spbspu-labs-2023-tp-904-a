#include "read_polygons.h"
#include <fstream>
#include <string>
#include <iterator>
#include <limits>

std::vector< tarasenko::Polygon > tarasenko::readPolygons(std::ifstream& in)
{
  std::vector< Polygon > polygons;
  using in_iter = std::istream_iterator< Polygon >;
  while (!in.eof())
  {
    std::copy(in_iter(in), in_iter(), std::back_inserter(polygons));
    if (!in)
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return polygons;
}
