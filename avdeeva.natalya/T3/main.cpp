#include <iostream>
#include <iterator>
#include <fstream>
#include <deque>
#include "polygon.h"
int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Not enough CL parameters" << '\n';
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "File not open" << '\n';
    return 2;
  }
  std::deque< avdeeva::Polygon > polygons;
  while (!input.eof())
  {
    std::copy(std::istream_iterator< avdeeva::Polygon >(input),
      std::istream_iterator< avdeeva::Polygon >(),
      std::back_inserter(polygons));
    if (input.fail())
    {
      input.clear();
      auto maxstream = std::numeric_limits< std::streamsize >::max();
      input.ignore(maxstream, '\n');
    }
  }
}
