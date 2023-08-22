#include <fstream>
#include "point-struct.hpp"
#include <sstream>
#include <iostream>
int main()//int argc, char * argv[])
{
  turkin::Point a;
  std::istringstream iss("(1;2) (3;4)");
  iss >> a;
  std::cout << a.x << " " << a.y << "\n";
}
