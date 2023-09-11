#include <iostream>
#include "point.h"

int main()
{
  kryuchkova::Point point;
  while (std::cin)
  {
    std::cin >> point;
    std::cout << point.x << ' ' << point.y;
  }
}
