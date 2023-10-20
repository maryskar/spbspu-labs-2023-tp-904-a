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

  std::map< std::string, std::function< void() > > commands = {
    {"AREA", std::bind(skarlygina::getArea, std::ref(polygons), std::ref(std::cin), std::ref(std::cout))},
    {"MAX", std::bind(skarlygina::getMax, std::ref(polygons), std::ref(std::cin), std::ref(std::cout))},
    {"MIN", std::bind(skarlygina::getMin, std::ref(polygons), std::ref(std::cin), std::ref(std::cout))},
    {"COUNT", std::bind(skarlygina::countFigures, std::ref(polygons), std::ref(std::cin), std::ref(std::cout))},
    {"PERMS", std::bind(skarlygina::findPerms, std::ref(polygons), std::ref(std::cin), std::ref(std::cout))},
    {"SAME", std::bind(skarlygina::findSame, std::ref(polygons), std::ref(std::cin), std::ref(std::cout))}
  };

  while (!std::cin.eof())
  {
    std::cin.clear();
    std::string command = "";
    std::cin >> command;
    if (command.empty())
    {
      continue;
    }
    try
    {
      commands.at(command)();
    }
    catch (const std::exception& e)
    {
      skarlygina::printInvalidCommand(std::cout);
      std::cout << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
