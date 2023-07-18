#include <iostream>
#include <fstream>
#include <limits>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>
#include "polygon.hpp"
#include "commands.hpp"
int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid quantity of arguments\n";
    return -1;
  }
  std::ifstream fin(argv[1]);
  if (!fin.is_open())
  {
    std::cerr << "File wasn't opened\n";
    return -1;
  }
  std::vector< litvin::Polygon > data;
  auto max_num = std::numeric_limits< std::streamsize >::max();
  while (!fin.eof())
  {
    if (fin.fail())
    {
      fin.clear();
      fin.ignore(max_num, '\n');
    }
    using is_it = std::istream_iterator< litvin::Polygon >;
    std::copy(is_it(fin), is_it(), std::back_inserter(data));
  }
  return 0;
}
