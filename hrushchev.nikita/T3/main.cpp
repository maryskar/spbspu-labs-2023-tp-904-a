#include <iostream>
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

int main()
{
  hrushchev::Polygon a;
  std::cin >> a;
  auto b = getArea(a);
  printPolygon(a);
  std::cout << b << "\n";
}
