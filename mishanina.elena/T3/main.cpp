#include <iostream>
#include <sstream>
#include <limits>
#include "Polygon.h"
int main()
{
  using namespace mishanina;
  std::stringstream input{
    "3 (0;0) (1;1) (1;0)\n"
    "2 (0;0) (1;1)\n"
    "\n"
    "4 (0;0) (1;0) (1;1) (0;1)\n"
  };
  std::vector<Polygon> pol;
  while (!input.eof())
  {
    std::copy(std::istream_iterator<Polygon>(input),
              std::istream_iterator<Polygon>(),
              std::back_inserter(pol));
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  for (Polygon &pl: pol)
  {
    std::cout << "point\n";
    for (auto &point: pl.points)
    {
      std::cout << "x = " << point.x << "\ty = " << point.y << '\n';
    }
  }
  return 0;
}
