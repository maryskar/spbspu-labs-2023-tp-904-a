#ifndef T3_HELPFUNCTIONS_HPP
#define T3_HELPFUNCTIONS_HPP
#include <map>
#include <tuple>
#include "Polygon.hpp"
namespace malaya
{
  std::string inputCommand(std::istream & in);
  std::ostream & invalidPrint(std::ostream & out);
  class Commands
  {
   public:
    Commands();
    void doComm(const std::string &, const std::vector< Polygon > &, std::ostream &) const;
    void doComm(const std::string &, const std::vector< Polygon > &, size_t, std::ostream &) const;
    void doComm(const std::string &, const std::vector< Polygon > &, std::ostream &, std::istream &) const;
   private:
    using firstComType = void (*)(const std::vector< Polygon > & data, std::ostream & out);
    using secondComType = void (*)(const std::vector< Polygon > & data, size_t num, std::ostream & out);
    using thirdComType = void (*)(const std::vector< Polygon > & data, std::ostream & out, std::istream & in);
    using firstDict = std::map< std::string, firstComType >;
    using secondDict = std::map< std::string, secondComType >;
    using thirdDict = std::map< std::string, thirdComType >;
    firstDict dict1_;
    secondDict dict2_;
    thirdDict dict3_;
  };

  void doCommand(const std::vector< Polygon > &, const Commands &, std::string &, std::istream &, std::ostream &);
}
#endif
