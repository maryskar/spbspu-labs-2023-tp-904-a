#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <fstream>
#include <deque>
#include <limits>
#include <sstream>
#include <map>
#include "polygon.h"
#include "commands.h"

int main(int argc, char ** argv)
{
  using namespace shestakov;
  if (argc != 2)
  {
    std::cerr << "Not enough CL parameters\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  /*
  std::stringstream input(
    "3 (0;0) (1;0) (1;6)\n"
    "2 (0;1) (1;0)\n"
    "\n"
    "4 (0;0) (2;0) (2;2) (0;2)\n"
    );*/
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
  using const_cmd_t = std::function< void (const std::vector< Polygon >&, std::ostream&) >;
  using const_cmd_t_in = std::function< void (const std::vector< Polygon >&, size_t num, std::ostream&) >;
  using cmd_t = std::function< void (std::vector< Polygon >&, std::istream&, std::ostream&, std::ostream&) >;
  std::map< std::string, const_cmd_t > const_cmds
  {
    {"AREA EVEN", areaEven},
    {"AREA ODD", areaOdd},
    {"AREA MEAN", areaMean},
    {"MAX AREA", maxArea},
    {"MAX VERTEXES", maxVertexes},
    {"MIN AREA", minArea},
    {"MIN VERTEXES", minVertexes},
    {"COUNT EVEN", countEven},
    {"COUNT ODD", countOdd}
  };
  std::map< std::string, const_cmd_t_in > const_cmds_in
  {
    {"COUNT NUM", countVert},
    {"AREA NUM", areaVert}
  };
  while (!std::cin.eof())
  {
    std::string cmd;
    std::getline(std::cin, cmd);
    if (cmd.empty())
    {
      continue;
    }
    try {
      auto toexecute = const_cmds.at(cmd);
      toexecute(polygons, std::cout);
    }
    catch (...){
      try
      {
        size_t num = std::stoull(cmd.substr(cmd.find_first_of(' ')));
        cmd = (cmd.substr(0, cmd.find(' ')) + " NUM");
        auto toexecute = const_cmds_in.at(cmd);
        toexecute(polygons, num, std::cout);
      }
      catch (...)
      {
        //skipUntilNewLine(std::cin);
        std::cout << "<INVALID COMMAND>\n";
      }
    }
  }
}
