#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <deque>
#include <limits>
#include <sstream>
#include "polygon.h"
#include "read_and_do_commands.h"
#include "auxiliary_commands.h"

int main(int argc, char ** argv)
{
  using namespace shestakov;
  if (argc != 2)
  {
    std::cerr << "Not enough CL parameters\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  std::vector< Polygon > polygons;
  auto maxstream = std::numeric_limits< std::streamsize >::max();
  while (!input.eof())
  {
    std::copy(std::istream_iterator< Polygon >(input), std::istream_iterator< Polygon >(),
      std::back_inserter(polygons));
    if (input.fail())
    {
      input.clear();
      input.ignore(maxstream, '\n');
    }
  }
  while (!std::cin.eof())
  {
    std::string cmd = "";
    std::cin >> cmd;
    try
    {
      if (polygons.empty())
      {
        throw std::logic_error("");
      }
      doCommand(polygons, std::cin, std::cout, cmd);
    }
    catch (const std::logic_error &e)
    {
      printError(std::cout);
      skipUntilNewLine(std::cin);
      std::cin.clear();
    }
    catch (const std::runtime_error &e)
    {
      break;
    }
  }
}
