#ifndef COMMANDS_H
#define COMMANDS_H

#include <iosfwd>
#include <map>
#include "Geometry.h"

namespace ganiullin {
  void printAreaEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void printAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void printAreaMean(const std::vector< Polygon >& polygons, std::ostream& out);
  void printMaxArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void printMinArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void printMaxVertexNum(const std::vector< Polygon >& polygons,
      std::ostream& out);
  void printMinVertexNum(const std::vector< Polygon >& polygons,
      std::ostream& out);
  void printCountEven(const std::vector< Polygon >& polygons,
      std::ostream& out);
  void printCountOdd(const std::vector< Polygon >& polygons, std::ostream& out);

  void printAreaVertexNum(const std::vector< Polygon >& polygons,
      size_t vertexNum, std::ostream& out);
  void printCountVertexNum(const std::vector< Polygon >& polygons,
      size_t vertexNum, std::ostream& out);

  void printInFrame(const std::vector< Polygon >& polygons, const Polygon& fig,
      std::ostream& out);
  void printSame(const std::vector< Polygon >& polygons, const Polygon& fig,
      std::ostream& out);

  struct command_dicts_t {
    std::map< std::string, void (*)(const std::vector< Polygon >& polygons,
                               const Polygon& fig, std::ostream& out) >
        polygonCommandDict;
    std::map< std::string, void (*)(const std::vector< Polygon >& polygons,
                               const size_t vertexes, std::ostream& out) >
        vertexCommandDict;
    std::map< std::string,
        void (*)(const std::vector< Polygon >& polygons, std::ostream& out) >
        stateCommandDict;
  };
  std::string readCommand(std::istream& in, const command_dicts_t& commandDict);
  void executeCommand(const std::string& command,
      const std::vector< Polygon > polygons, command_dicts_t commandDicts,
      std::istream& in, std::ostream& out);

  void printErrorMessage(std::ostream& out);
  command_dicts_t createCommandDicts();
}
#endif
