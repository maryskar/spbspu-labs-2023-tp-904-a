#ifndef T3_COMMANDS_HPP
#define T3_COMMANDS_HPP
#include <map>
#include "polygon.hpp"
namespace litvin
{
  using signature_type_1 = void (*)(const std::vector< Polygon > & data, std::ostream & out);
  using signature_type_2 = void (*)(const std::vector< Polygon > & data, const Polygon & pol, std::ostream & out);
  using signature_type_3 = void (*)(const std::vector< Polygon > & data, size_t num, std::ostream & out);
  struct command_dicts
  {
    std::map< std::string, signature_type_1 > dict1;
    std::map< std::string, signature_type_2 > dict2;
    std::map< std::string, signature_type_3 > dict3;
  };
  //command_dicts initializeCommandDicts();
}
#endif
