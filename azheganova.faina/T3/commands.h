#ifndef COMMANDS_H
#define COMMANDS_H
#include <map>
#include "datastructs.h"

namespace azheganova
{
  using str = std::string;
  using vec = std::vector< Polygon >;
  class Commands
  {
   public:
    Commands();
    void doComm(const str & comm, const std::vector< Polygon > & data, std::ostream & out) const;
    void doComm(const str & comm, const std::vector< Polygon > & data, size_t num, std::ostream & out) const;
    void doComm(const str & comm, const std::vector< Polygon > & data, std::ostream & out, std::istream & in) const;
   private:
    using commands1 = void (*) (const std::vector< Polygon > & polygon, std::ostream & out);
    using commands2 = void (*) (const std::vector< Polygon > & polygon, size_t num, std::ostream & out);
    using commands3 = void (*)(const std::vector< Polygon > & polygon, std::ostream & out, std::istream & in);
    std::map< std::string, commands1 > dict_1;
    std::map< std::string, commands2 > dict_2;
    std::map< std::string, commands3 > dict_3;
  };
  bool isEven(const Polygon & polygon);
  bool isOdd(const Polygon & polygon);
  void getAreaEven(const std::vector< Polygon > & polygon, std::ostream & out);
  void getAreaOdd(const std::vector< Polygon > & polygon, std::ostream & out);
  void getAreaMean(const std::vector< Polygon > & polygon, std::ostream & out);
  double isCountVertex(const Polygon & polygon, size_t vertexcount);
  void getAreaNumOfVertexes(const std::vector< Polygon > & polygon, size_t num, std::ostream & out);
  void getMaxArea(const std::vector< Polygon > & polygon, std::ostream & out);
  void getMaxVertexes(const std::vector< Polygon > & polygon, std::ostream & out);
  void getMinArea(const std::vector< Polygon > & polygon, std::ostream & out);
  void getMinVertexes(const std::vector< Polygon > & polygon, std::ostream & out);
  void countEven(const std::vector< Polygon > & polygon, std::ostream & out);
  void countOdd(const std::vector< Polygon > & polygon, std::ostream & out);
  void countNumOfVertexes(const std::vector< Polygon > & polygon, size_t num, std::ostream & out);
  bool isCompareRmecho(const Polygon & first, const Polygon & second, const Polygon & polygon);
  void getRmecho(const std::vector< Polygon > & polygon, std::ostream & out, std::istream & in);
  void getRightshapes(const std::vector< Polygon > & polygon, std::ostream & out);
  std::string inputCommand(std::istream & in);
  void doCommand(const str & command, const Commands & com, const vec & polygon, std::istream & in, std::ostream & out);
  std::ostream & printInvalidCommand(std::ostream & out);
}

#endif
