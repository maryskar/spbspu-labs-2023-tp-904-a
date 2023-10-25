#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <sstream>
#include "commands.h"
#include "dict.h"

int main() {
  std::vector< chulkov::Dict > dicts;
  std::map< std::string, std::function< void(std::istream&, std::ostream&, std::vector< chulkov::Dict >&) > > commandsMap =
          {
             {"save", chulkov::save},
             {"print", chulkov::print},
             {"printMaxCountWords", chulkov::printMaxCountWords},
             {"search", chulkov::search},
             {"clear", chulkov::clear},
             {"load", chulkov::load},
             {"remove", chulkov::remove},
             {"count", chulkov::count},
             {"union", chulkov::unionData},
             {"insert", chulkov::insert},
             {"intersect", chulkov::intersect},
             {"size", chulkov::getSize}
          };
  std::string command;
  while (std::cin >> command) {
    if (commandsMap.find(command) != commandsMap.end()) {
      commandsMap.at(command)(std::cin, std::cout, dicts);
    } else {
      std::cout << "Invalid command: " << command << '\n';
    }
  }
  return 0;
}
