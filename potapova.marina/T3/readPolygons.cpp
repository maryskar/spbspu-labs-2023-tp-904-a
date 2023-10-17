#include "readPolygons.h"
#include <algorithm>
#include <iterator>
#include "workWithIO.h"

namespace potapova
{
  std::deque< Polygon > readPolygons(std::istream& in)
  {
    std::deque< Polygon > polygons;
    while (!in.eof())
    {
      std::copy(std::istream_iterator< Polygon >(in),
        std::istream_iterator< Polygon >(),
        std::back_inserter(polygons));
    }
    return polygons;
  }
}
