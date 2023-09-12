#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include "point.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Wrong input\n";
    return -1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Something wrong with file\n";
    return 2;
  }
  std::deque< zhuravlev::Polygon > polygons;
  while (!input.eof())
  {
    try
    {
      using in_pol_iter = std::istream_iterator< zhuravlev::Polygon >;
      std::copy(in_pol_iter(input), in_pol_iter(), std::back_inserter(polygons));
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what();
      return -1;
    }
  }
  return 0;
}
