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
    void doComm(const str & comm, std::vector< Polygon > & data, std::ostream & out) const;
    void doComm(const str & comm, std::vector< Polygon > & data, size_t num, std::ostream & out) const;
    void doComm(const str & comm, std::vector< Polygon > & data, std::ostream & out, std::istream & in) const;
   private:
    using commands1 = void (*) (std::vector< Polygon > & polygon, std::ostream & out);
    using commands2 = void (*) (std::vector< Polygon > & polygon, size_t num, std::ostream & out);
    using commands3 = void (*) (std::vector< Polygon > & polygon, std::ostream & out, std::istream & in);
    std::map< std::string, commands1 > dict_1;
    std::map< std::string, commands2 > dict_2;
    std::map< std::string, commands3 > dict_3;
  };
  bool isEven(const Polygon & polygon);
  bool isOdd(const Polygon & polygon);
  void getAreaEven(std::vector< Polygon > & polygon, std::ostream & out);
  void getAreaOdd(std::vector< Polygon > & polygon, std::ostream & out);
  void getAreaMean(std::vector< Polygon > & polygon, std::ostream & out);
  double isCountVertex(const Polygon & polygon, size_t vertexcount);
  void getAreaNumOfVertexes(std::vector< Polygon > & polygon, size_t num, std::ostream & out);
  void getMaxArea(std::vector< Polygon > & polygon, std::ostream & out);
  void getMaxVertexes(std::vector< Polygon > & polygon, std::ostream & out);
  void getMinArea(std::vector< Polygon > & polygon, std::ostream & out);
  void getMinVertexes(std::vector< Polygon > & polygon, std::ostream & out);
  void countEven(std::vector< Polygon > & polygon, std::ostream & out);
  void countOdd(std::vector< Polygon > & polygon, std::ostream & out);
  void countNumOfVertexes(std::vector< Polygon > & polygon, size_t num, std::ostream & out);
  bool isCompareRmecho(const Polygon & first, const Polygon & second, const Polygon & polygon);
  void getRmecho(std::vector< Polygon > & polygon, std::ostream & out, std::istream & in);
  void getRightshapes(std::vector< Polygon > & polygon, std::ostream & out);
  std::string inputCommand(std::istream & in);
  void doCommand(const str & command, const Commands & com, vec & polygon, std::istream & in, std::ostream & out);
  std::ostream & printInvalidCommand(std::ostream & out);
}

#endif
