#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <limits>
#include "polygon.h"
#include "read_and_do_commands.h"
#include "auxiliary_commands.h"

int main(int argc, char ** argv)
{
  using is_it = std::istream_iterator< shestakov::Polygon >;
  if (argc != 2)
  {
    std::cerr << "Not enough CL parameters\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  std::vector< shestakov::Polygon > polygons;
  auto maxstream = std::numeric_limits< std::streamsize >::max();
  while (!input.eof())
  {
    std::copy(is_it(input), is_it(), std::back_inserter(polygons));
    if (input.fail())
    {
      input.clear();
      input.ignore(maxstream, '\n');
    }
  }
  while (!std::cin.eof())
  {
    try
    {
      std::string cmd = shestakov::readCommand(std::cin);
      doCommand(polygons, std::cin, std::cout, cmd);
    }
    catch (const std::logic_error &e)
    {
      shestakov::skipUntilNewLine(std::cin);
      std::cin.clear();
      shestakov::printError(std::cout);
      std::cout << '\n';
    }
    catch (const std::runtime_error &e)
    {
      break;
    }
    std::cin.clear();
  }
}
