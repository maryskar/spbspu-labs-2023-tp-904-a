#include "readPolygons.h"
#include <algorithm>
#include <iterator>
#include <limits>
#include "workWithIO.h"

std::deque< potapova::Polygon > potapova::readPolygons(std::istream& in)
{
  std::deque< Polygon > polygons;
  while (!in.eof())
  {
    std::move(std::istream_iterator< Polygon >(in),
      std::istream_iterator< Polygon >(),
      std::back_inserter(polygons));
    in.clear(std::ios_base::goodbit);
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return polygons;
}
