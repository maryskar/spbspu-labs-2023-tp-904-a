#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "commands.h"
#include "dict.h"

int main() {
  try {
    std::vector< chulkov::Dict > dicts;
    std::map< std::string, std::function< void() > > commandsMap =
            {
                    {"save", std::bind(chulkov::save, std::ref(std::cin), std::ref(dicts))},
                    {"print", std::bind(chulkov::print, std::ref(std::cin), std::ref(std::cout), std::ref(dicts))},
                    {"printMaxCountWords", std::bind(chulkov::printMaxCountWords, std::ref(std::cin), std::ref(std::cout), std::ref(dicts))},
                    {"search", std::bind(chulkov::search, std::ref(std::cin), std::ref(std::cout), std::ref(dicts))},
                    {"clear", std::bind(chulkov::clear, std::ref(std::cin), std::ref(dicts))},
                    {"load", std::bind(chulkov::load, std::placeholders::_1, std::ref(dicts))},
                    {"remove", std::bind(chulkov::remove, std::ref(std::cin), std::ref(dicts))},
                    {"count", std::bind(chulkov::count, std::ref(std::cin), std::ref(std::cout), std::ref(dicts))},
                    {"union", std::bind(chulkov::unionData, std::placeholders::_1, std::placeholders::_2, std::ref(dicts))},
                    {"insert", std::bind(chulkov::insert, std::ref(std::cin), std::ref(dicts))},
                    {"intersect", std::bind(&chulkov::intersect, std::placeholders::_1, std::placeholders::_2)},
                    {"size", std::bind(chulkov::getSize, std::ref(dicts))}};
    std::string command{};
    while (!std::cin.eof()) {
      std::cin >> command;
      commandsMap.at(command)();
    }
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what();
  }
}
