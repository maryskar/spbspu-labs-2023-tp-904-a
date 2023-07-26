#ifndef T3_COMMANDS_HPP
#define T3_COMMANDS_HPP
#include <string>
#include <map>
#include "polygon.hpp"
namespace litvin
{
  using name1 = void (*)(const std::vector< Polygon > & data, std::ostream & out);
  using name2 = void (*)(const std::vector<Polygon> & data, const Polygon & pol, std::ostream & out);
  using name3 = void (*)(const std::vector< Polygon > & data, size_t num, std::ostream & out);
  struct commandDict
  {
    std::map< std::string, name1 > dict1;
    std::map< std::string, name2 > dict2;
    std::map< std::string, name3 > dict3;
  };
}
#endif
