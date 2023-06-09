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
    using firstComType = void (*)(const std::vector< Polygon > & data, std::ostream & out);
    using secondComType = void (*)(const std::vector< Polygon > & data, size_t num, std::ostream & out);
    using thirdComType = void (*)(const std::vector< Polygon > & data, std::ostream & out, std::istream & in);
    using firstDict = std::map< std::string, firstComType >;
    using secondDict = std::map< std::string, secondComType >;
    using thirdDict = std::map< std::string, thirdComType >;
    Commands();
    //const firstDict & getFirst() const;
    //const secondDict & getSecond() const;
    //const thirdDict & getThird() const;
    void doComm(const std::string &, const std::vector< Polygon > &, std::ostream &) const;
    void doComm(const std::string &, const std::vector< Polygon > &, size_t, std::ostream &) const;
    void doComm(const std::string &, const std::vector< Polygon > &, std::ostream &, std::istream &) const;
   private:
    firstDict dict1;
    secondDict dict2;
    thirdDict dict3;
  };

  void doCommand(const std::vector< Polygon > &, const Commands &, std::string &, std::istream &, std::ostream &);
}
#endif
