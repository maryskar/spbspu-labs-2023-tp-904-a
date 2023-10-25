#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <sstream>
#include "commands.h"
#include "dict.h"

int main() {
  using cmdType = std::function< void(std::istream&, std::ostream&, std::vector< chulkov::Dict >&) >;
  std::vector< chulkov::Dict > dicts;
  std::map< std::string, cmdType >  commandsMap;
  commandsMap.insert({"save", chulkov::save});
  commandsMap.insert({"print", chulkov::print});
  commandsMap.insert({"printMaxCountWords", chulkov::printMaxCountWords});
  commandsMap.insert({"search", chulkov::search});
  commandsMap.insert({"clear", chulkov::clear});
  commandsMap.insert({"load", chulkov::load});
  commandsMap.insert({"remove", chulkov::remove});
  commandsMap.insert({"count", chulkov::count});
  commandsMap.insert({"union", chulkov::unionData});
  commandsMap.insert({"insert", chulkov::insert});
  commandsMap.insert({"intersect", chulkov::intersect});
  commandsMap.insert({"size", chulkov::getSize});
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
