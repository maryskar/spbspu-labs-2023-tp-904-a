#ifndef T3_COMMANDS_H
#define T3_COMMANDS_H
#include <map>
#include "polygon.h"

namespace vagina
{
  void areaEven(const std::vector< Polygon >& dest, std::ostream& out);
  void areaOdd(const std::vector< Polygon >& dest, std::ostream& out);
  void areaMean(const std::vector< Polygon >& dest, std::ostream& out);
  void areaVertexes(const std::vector< Polygon >& dest, std::ostream& out, std::size_t param);
  void maxArea(const std::vector < Polygon >& dest, std::ostream& out);
  void maxVertexes(const std::vector < Polygon >& dest, std::ostream& out);
  void minArea(const std::vector < Polygon >& dest, std::ostream& out);
  void minVertexes(const std::vector < Polygon >& dest, std::ostream& out);
  void countEven(const std::vector < Polygon >& dest, std::ostream& out);
  void countOdd(const std::vector < Polygon >& dest, std::ostream& out);
  void countVertexes(const std::vector < Polygon >& dest, std::ostream& out, std::size_t param);
  void rects(const std::vector < Polygon >& dest, std::ostream& out);
  void perms(const std::vector < Polygon >& dest, std::ostream& out, std::istream& in);
  bool isEven(const Polygon& pol);
  bool isOdd(const Polygon& pol);
  bool isCountOfVertexes(const Polygon& pol, std::size_t param);
  bool isPerm(const Polygon& lhs, const Polygon& rhs);
  void messageInvalidCommand(std::ostream& out);
  class DictionaryOfCommands
  {
    public:
      DictionaryOfCommands();
      void doCommPoly(const std::string& command, const std::vector< Polygon >& data, std::ostream& out) const;
      void doCommVert(const std::string& command, const std::vector< Polygon >& data, std::ostream& out, size_t n) const;
      void doCommPerms(const std::string&, const std::vector< Polygon >&, std::ostream&, std::istream&) const;
    private:
      using commandPolygon = void(*)(const std::vector< Polygon >& data, std::ostream& out);
      using commandVertexes = void(*)(const std::vector< Polygon >& data, std::ostream& out, size_t n);
      using commandPerms = void(*)(const std::vector< Polygon >& data, std::ostream& out, std::istream& in);
      std::map< std::string, commandPolygon > polygon;
      std::map< std::string, commandVertexes > vertexes;
      std::map< std::string, commandPerms > permutation;
  };
  std::string readCommand(std::istream& in);
  void doCommand(const std::string& command, const DictionaryOfCommands& commands, const std::vector< Polygon >& data,
    std::istream& in, std::ostream& out);
}


#endif
