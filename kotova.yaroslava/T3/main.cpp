#include <iostream>
#include <iterator>
#include <fstream>
#include <functional>
#include <limits>
#include "geomfigures.hpp"
int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error." << '\n';
    return 1;
  }
  std::ifstream input(argv[1]);
  std::vector< kotova::Polygon > polygons;
  while (!input.eof())
  {
    std::copy(std::istream_iterator< kotova::Polygon >(input), std::istream_iterator< kotova::Polygon >(), std::back_inserter(polygons));
  }
  if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
}