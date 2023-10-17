#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include <vector>
#include "commands.h"
#include "polygon.h"

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "Invalid number of arg";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in) {
    std::cerr << "File is not open";
    return 1;
  }

  std::vector< chulkov::Polygon > poligons;
  using vectorOfPoligons = std::vector< chulkov::Polygon >;
  using istiter = std::istream_iterator< chulkov::Polygon >;
  while (!in.eof()) {
    std::copy(istiter(in), istiter(), std::back_inserter(poligons));
    if (!in) {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  using command_t = std::function< void(vectorOfPoligons&, std::istream&, std::ostream&) >;
  std::map< std::string, command_t > commands = {
      {"AREA", chulkov::getArea},
      {"MAX", chulkov::getMax},
      {"MIN", chulkov::getMin},
      {"COUNT", chulkov::getCount},
      {"PERMS", chulkov::getPerms},
      {"RMECHO", chulkov::getRmecho}
  };

  while (!std::cin.eof()) {
    std::string command = "";
    std::cin >> command;
    if (!command.empty()) {
      try {
        commands.at(command)(poligons, std::cin, std::cout);
      } catch (const std::exception& e) {
        std::cout << "<INVALID COMMAND>"<< "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
  }
  return 0;
}
