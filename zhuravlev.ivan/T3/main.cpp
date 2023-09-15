#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <sstream>
#include "polygon.hpp"
#include "commands.hpp"
#include "sub_commands.hpp"

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
    std::cout << polygons.size() << "\n";
    std::copy(polygons.cbegin(), polygons.cend(), std::ostream_iterator< zhuravlev::Polygon >(std::cout, "\n"));
  }
  using const_cmd_t = std::function< void (const std::vector< zhuravlev::Polygon >&, std::ostream&) >;
  using cmd_t = std::function< void (std::vector< zhuravlev::Polygon >&, std::istream&, std::ostream&, std::ostream&) >;
  std::map< std::string, const_cmd_t > const_cmds
  {
    {"COUNT ODD", zhuravlev::countOdd},
    {"COUNT EVEN", zhuravlev::countEven},
    {"MAX AREA", zhuravlev::MaxArea},
    {"MAX VERTEXES", zhuravlev::MaxVertexes},
    {"AREA MEAN", zhuravlev::AreaMean},
    {"AREA EVEN", zhuravlev::AreaEven},
    {"AREA ODD", zhuravlev::AreaOdd},
    //{"AREA", zhuravlev::AreaVertexes},
    {"MIN AREA", zhuravlev::MinArea},
    {"MIN VERTEXES", zhuravlev::MinVertexes},
    {"COUNT", zhuravlev::countVertexes}
  };
  while (!std::cin.eof())
  {
    std::string cmd;
    std::getline(std::cin, cmd);
    if (cmd.empty())
    {
      continue;
    }
    try
    {
      auto toexecute = const_cmds.at(cmd);
      toexecute(polygons, std::cout);
    }
    catch(const std::exception& e)
    {
      e.what();
    }
  }
  return 0;
}
