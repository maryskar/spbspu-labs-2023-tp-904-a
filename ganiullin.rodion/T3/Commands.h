#ifndef COMMANDS_H
#define COMMANDS_H

#include <iosfwd>
#include <map>
#include "Geometry.h"

namespace ganiullin {

  std::ostream& printErrorMessage(std::ostream& out);

  class CommandHandler {
  public:
    CommandHandler();
    ~CommandHandler() = default;

    std::string readCommand(std::istream& in) const;
    std::ostream& executeCommand(const std::string& command, const std::vector< Polygon >& polygons,
        std::istream& in, std::ostream& out) const;

  private:
    using Polygons = std::vector< Polygon >;
    using PolygonCommand = std::ostream& (*)(const Polygons& polygons, const Polygon& fig, std::ostream& out);
    using VertexCommand = std::ostream& (*)(const Polygons& polygons, const size_t vertexes,
        std::ostream& out);
    using StateCommand = std::ostream& (*)(const Polygons& polygons, std::ostream& out);

    std::map< std::string, PolygonCommand > polygonCommandDict_;
    std::map< std::string, VertexCommand > vertexCommandDict_;
    std::map< std::string, StateCommand > stateCommandDict_;
  };
}
#endif
