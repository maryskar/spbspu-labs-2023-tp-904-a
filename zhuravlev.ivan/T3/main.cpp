#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <sstream>
#include "polygon.hpp"
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
    "8 (0;2) (0;4) (2;6) (4;6) (6;4) (6;2) (4;0) (2;0)\n"
    "3 (0;0) (2;0) (0;2)\n"
    "8 (0;2) (0;4) (2;6) (4;6) (6;4) (6;2) (4;0) (2;0)\n"
    };
  while (!input.eof())
  {
    using in_pol_iter = std::istream_iterator< zhuravlev::Polygon >;
    std::copy(in_pol_iter(input), in_pol_iter(), std::back_inserter(polygons));
    std::copy(polygons.cbegin(), polygons.cend(), std::ostream_iterator< zhuravlev::Polygon >(std::cout, "\n"));
  }
  while (!std::cin.eof())
  {
    try
    {
      zhuravlev::doCommand(polygons, std::cout, zhuravlev::readCommand(std::cin));
    }
    catch(const std::logic_error& e)
    {
      zhuravlev::skipUntilNewLines(std::cin);
      zhuravlev::printError(std::cout);
    }
  }
  return 0;
}
