#include <iostream>
#include <vector>
#include <exception>
#include <fstream>
#include <functional>
#include <map>
#include <limits>
#include <iterator>
#include "polygon.h"
#include "commands.h"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Invalid number of arguments";
    return 1;
  }
  std::ifstream fin(argv[1]);
  if (!fin)
  {
    std::cerr << "File is not open";
    return 1;
  }
  std::vector< skarlygina::Polygon > polygons;
  using iterator_istream = std::istream_iterator< skarlygina::Polygon >;

  while (!fin.eof())
  {
    std::copy(iterator_istream(fin), iterator_istream(), std::back_inserter(polygons));
    if (!fin)
    {
      fin.clear();
      fin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  using cmd_t = std::function< void(const std::vector< skarlygina::Polygon >&, std::istream&, std::ostream&) >;
  std::map< std::string, cmd_t > commands = {
    {"AREA", skarlygina::getArea},
    {"MAX", skarlygina::getMax},
    {"MIN", skarlygina::getMin},
    {"COUNT", skarlygina::countFigures},
    {"PERMS", skarlygina::findPerms},
    {"SAME", skarlygina::findSame}
  };

  while (!std::cin.eof())
  {
    std::string command;
    std::cin >> command;
    if (std::cin.eof())
    {
      continue;
    }
    try
    {
      auto try_ex = commands.at(command);
      Iofmtguard ofmtguard(std::cout);
      try_ex(polygons, std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      skarlygina::printInvalidCommand(std::cout);
    }
  }
}
