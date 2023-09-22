#include <iostream>
#include <sstream>
#include "polygon.h"

int main()
{
  std::stringstream sstr("3 (1; 1) (1; 3) (3; 3)\n"
    "4 (0; 0) (0; 1) (1; 1) (1; 0)\n"
    "5 (0; 0) (0; 1) (1; 2) (2; 1) (2; 0)\n"
    "3 (0; 0) (-2; 0) (0; -2));\n");

  std::vector< dmitriev::Polygon > polygons;

  while (!sstr.eof())
  {
    std::copy(std::istream_iterator< dmitriev::Polygon >(sstr),
      std::istream_iterator< dmitriev::Polygon >(),
      std::back_inserter(polygons));

    if (sstr.fail())
    {
      sstr.clear();
      sstr.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
