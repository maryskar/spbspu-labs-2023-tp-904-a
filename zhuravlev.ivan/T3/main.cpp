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
  //constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
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
    if (input.fail())
    {
      input.clear();
      zhuravlev::skipUntilNewLines(std::cin);
    }
    using in_pol_iter = std::istream_iterator< zhuravlev::Polygon >;
    std::copy(in_pol_iter(input), in_pol_iter(), std::back_inserter(polygons));
  }
  while (!std::cin.eof())
  {
    try
    {
      std::string cmd = zhuravlev::readCommand(std::cin);
      zhuravlev::doCommand(polygons, std::cin, std::cout, cmd);
    }
    catch(const std::logic_error& e)
    {
      std::cin.clear();
      zhuravlev::printError(std::cout);
    }
    catch(const std::runtime_error& e)
    {
      break;
    }
    if (!std::cin)
    {
      std::cin.clear();
      zhuravlev::skipUntilNewLines(std::cin);
    }
  }
  return 0;
}
