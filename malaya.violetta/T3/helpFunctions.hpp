#ifndef T3_HELPFUNCTIONS_HPP
#define T3_HELPFUNCTIONS_HPP
#include <map>
#include <tuple>
#include "Polygon.hpp"

namespace malaya
{
  std::string inputCommand(std::istream & in);
  void doCommand(const std::vector< malaya::Polygon > & data, std::string & command, std::istream & in, std::ostream & out);
  void invalidPrint(std::ostream & out);
  using firstComType = void(*)(const std::vector< Polygon > & data, std::ostream & out);
  using secondComType = void(*)(const std::vector< Polygon > & data, size_t num, std::ostream & out);
  using thirdComType = void(*)(const std::vector< Polygon > & data, std::ostream & out, const Polygon & polygon);
  using firstDict = std::map< std::string, firstComType >;
  using secondDict = std::map< std::string, secondComType >;
  using thirdDict = std::map< std::string, thirdComType >;
  std::tuple< firstDict , secondDict , thirdDict > makeDictionary();
}
#endif
