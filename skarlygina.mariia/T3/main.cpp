#include <iostream>
#include <vector>
#include <exception>
#include <fstream>
#include "polygon.h"
#include "commands.h"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Invalid number of arguments";
    return 1;
  }
  std::ifstream fin(argv[1]);
  if (!fin)
  {
    std::cerr << "File is not open";
    return 1;
  }
  std::vector< skarlygina::Polygon > polygons;
  using vector_of_polygons = std::vector< skarlygina::Polygon >;
  using iterator_istream = std::istream_iterator< skarlygina::Polygon >;
  while (!fin.eof())
  {
    std::copy(iterator_istream(fin), iterator_istream(), std::back_inserter(polygons));
    if (!fin)
    {
      fin.clear();
      fin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

}