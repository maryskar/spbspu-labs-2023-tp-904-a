#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <deque>
#include "polygon.hpp"
#include "command.hpp"

void printPolygon(const hrushchev::Polygon& polygon)
{
  std::cout << "Polygon with " << polygon.points_.size() << " points:\n";
  for (const hrushchev::Point& point : polygon.points_)
  {
    std::cout << "(" << point.x_ << ", " << point.y_ << ")\n";
  }
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Error arg\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "Error file\n";
    return 1;
  }

  std::vector< hrushchev::Polygon > data;

  while (!input.eof())
  {
    if (!input)
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    using iter = std::istream_iterator< hrushchev::Polygon >;
    std::copy(iter(input), iter(), std::back_inserter(data));
  }
  for (auto i : data)
  {
    printPolygon(i);
  }
  for (auto i : data)
  {
    std::cout << getArea(i) << "\n";
  }
  std::cout << getAreaEven(data) << "\n";
}
