#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <sstream>
#include "polygon.hpp"
#include "commands.hpp"
#include "sub_commands.hpp"
#include "read_and_do_command.hpp"

int main(int argc, char* argv[])
{
  /*if (argc != 2)
  {
    std::cerr << "Wrong input\n";
    return -1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Something wrong with file\n";
    return 2;
  }*/
  std::vector< zhuravlev::Polygon > polygons;
  std::istringstream input{
    "3 (0;0) (1;1) (1;0)\n"
    "4 (0;0) (1;0) (1;1) (0;1)\n"
    "3 (0;0) (1;1) (1;0)\n"
    "4 (0;0) (2;0) (2;2) (0;2)\n"
    };
  while (!input.eof())
  {
    using in_pol_iter = std::istream_iterator< zhuravlev::Polygon >;
    std::copy(in_pol_iter(input), in_pol_iter(), std::back_inserter(polygons));
    std::cout << polygons.size() << "\n";
    std::copy(polygons.cbegin(), polygons.cend(), std::ostream_iterator< zhuravlev::Polygon >(std::cout, "\n"));
  }
  while (!std::cin.eof())
  {
    try
    {
      zhuravlev::readAndDoCommand(polygons, std::cin, std::cout);
    }
    catch(const std::exception& e)
    {
      e.what();
    }
  }
  return 0;
}
