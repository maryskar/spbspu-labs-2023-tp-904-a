#ifndef COMMANDS_H
#define COMMANDS_H

#include <iosfwd>
#include <map>
#include "Geometry.h"

namespace ganiullin {

  void printErrorMessage(std::ostream& out);

  class CommandHandler {
  private:
    using PolygonCommand = void (*)(const std::vector< Polygon >& polygons,
        const Polygon& fig, std::ostream& out);
    using VertexCommand = void (*)(const std::vector< Polygon >& polygons,
        const size_t vertexes, std::ostream& out);
    using StateCommand = void (*)(const std::vector< Polygon >& polygons,
        std::ostream& out);

    std::map< std::string, PolygonCommand > polygonCommandDict_;
    std::map< std::string, VertexCommand > vertexCommandDict_;
    std::map< std::string, StateCommand > stateCommandDict_;

    std::string readCommand(std::istream& in) const;
    void executeCommand(const std::string& command,
        const std::vector< Polygon > polygons, std::istream& in,
        std::ostream& out) const;

  public:
    CommandHandler();
    ~CommandHandler() = default;
    void readAndExecuteCommand(const std::vector< Polygon > polygons,
        std::istream& in, std::ostream& out) const;
  };
}
#endif
