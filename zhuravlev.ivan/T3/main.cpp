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
  std::vector< zhuravlev::Polygon > polygons;
  while (!input.eof())
  {
    using in_pol_iter = std::istream_iterator< zhuravlev::Polygon >;
    std::copy(in_pol_iter(input), in_pol_iter(), std::back_inserter(polygons));
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
    catch(const std::exception& e)
    {
      zhuravlev::skipUntilNewLines(std::cin);
      zhuravlev::printError(std::cout);
    }
  }
  return 0;
}
