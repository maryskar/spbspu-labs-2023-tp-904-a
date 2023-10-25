#include <iostream>
#include <iterator>
#include <fstream>
#include <functional>
#include <limits>
#include <numeric>
#include <string>
#include <map>
#include "commands.h"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cout << "error";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cout << "error";
    return 1;
  }
  std::vector< azheganova::Polygon > polygon;
  using ist_iter = std::istream_iterator< azheganova::Polygon >;
  while (!input.eof())
  {
    std::copy(ist_iter(input), ist_iter(), std::back_inserter(polygon));
    if (!input)
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  using com_t = std::function< void(std::vector< azheganova::Polygon > &) >;
  using namespace std::placeholders;
  const std::map< std::string, com_t > commands =
  {
    {"AREA", std::bind(azheganova::area, _1, std::ref(std::cin), std::ref(std::cout))},
    {"MAX", std::bind(azheganova::max, _1, std::ref(std::cin), std::ref(std::cout))},
    {"MIN", std::bind(azheganova::min, _1, std::ref(std::cin), std::ref(std::cout))},
    {"COUNT", std::bind(azheganova::count, _1, std::ref(std::cin), std::ref(std::cout))},
    {"RMECHO", std::bind(azheganova::rmecho, _1, std::ref(std::cin), std::ref(std::cout))},
    {"RIGHTSHAPES", std::bind(azheganova::rightshapes, _1, std::ref(std::cout))}
  };
  while (!std::cin.eof())
  {
    std::string command = "";
    std::cin >> command;
    if (!command.empty())
    {
      try
      {
        std::cout << std::setprecision(1) << std::fixed;
        commands.at(command)(polygon);
      }
      catch (const std::logic_error & e)
      {
        azheganova::printInvalidCommand(std::cout);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
  }
  return 0;
}
