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
      size_t parameter, std::ostream &ostream);

  using command_handler_poly = void (*)(std::vector< Polygon > &polygons,
      const Polygon &parameter, std::ostream &ostream);

  using umap = std::unordered_map< std::string, command_handler >;
  using umap_int = std::unordered_map< std::string, command_handler_int >;
  using umap_poly = std::unordered_map< std::string, command_handler_poly >;

  class CommandSystem {
  public:
    CommandSystem();
    const umap& getDict1() const;
    const umap_int& getDict2() const;
    const umap_poly& getDict3() const;

  private:
    umap dict1_;
    umap_int dict2_;
    umap_poly dict3_;
  };

  std::string inputCommand(std::istream &istream);
  void printInvalid(std::ostream &ostream);

  void handleCommand(const std::string &commandName,
      const CommandSystem &commandSystem, std::vector< Polygon > &polygons,
      std::istream &istream, std::ostream &ostream);
}

#endif
