#include <fstream>
#include "point-struct.hpp"
#include <sstream>
#include <iostream>
int main()//int argc, char * argv[])
{
  turkin::Polygon a;
  std::istringstream iss("3 (1;2) (3;4) (5;6)");
  iss >> a;
}
