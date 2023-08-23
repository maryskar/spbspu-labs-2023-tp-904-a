#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iterator>

#include "commands.hpp"
#include "point-struct.hpp"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "no file\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "cannot open file\n";
    return 1;
  }

  using cmd_t = std::ostream & (*)(std::vector< turkin::Polygon > &, std::istream &, std::ostream & out);
  std::map< std::string, cmd_t > list
  {
    {"AREA", turkin::area},
    {"MAX", turkin::max},
    {"MIN", turkin::min},
    {"COUNT", turkin::count},
    {"MAXSEQ", turkin::maxseq},
    {"RIGHTSHAPES", turkin::rightshapes}
  };

  std::vector< turkin::Polygon > data;
  std::copy(std::istream_iterator< turkin::Polygon >(file), std::istream_iterator< turkin::Polygon >(), std::back_inserter(data));

  while (std::cin)
  {
    std::string cmd;
    std::cin >> cmd;
    if (!std::cin)
    {
      break;
    }
    list[cmd](data, std::cin, std::cout) << "\n";
  }
}
