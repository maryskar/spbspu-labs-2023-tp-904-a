#ifndef T3_COMMAND_SYSTEM_H
#define T3_COMMAND_SYSTEM_H

#include <string>
#include <vector>
#include <unordered_map>
#include "polygon.h"

namespace kumachev {
  using command_handler = void (*)(const std::vector< Polygon > &polygons,
      std::ostream &ostream);

  using command_handler_int = void (*)(const std::vector< Polygon > &polygons,
      int parameter, std::ostream &ostream);

  using command_handler_poly = void (*)(const std::vector< Polygon > &polygons,
      const Polygon &parameter, std::ostream &ostream);

  struct CommandSystem {
    std::unordered_map< std::string, command_handler > dict1;
    std::unordered_map< std::string, command_handler_int > dict2;
    std::unordered_map< std::string, command_handler_poly > dict3;
  };

  std::string inputCommand(std::istream &istream);

  CommandSystem createCommandSystem();
  void printInvalid(std::ostream &ostream);

  void handleCommand(const std::string &commandName,
    std::vector< Polygon > &polygons,
    std::istream &istream,
    std::ostream &ostream);
}

#endif
