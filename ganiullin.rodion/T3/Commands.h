#ifndef COMMANDS_H
#define COMMANDS_H

#include <iosfwd>
#include <map>
#include "Geometry.h"

namespace ganiullin {

  std::ostream& printErrorMessage(std::ostream& out);
  std::ostream& printBool(std::ostream& out, bool val);

  class CommandHandler {
  public:
    CommandHandler();
    ~CommandHandler() = default;

    std::string readCommand(std::istream& in) const;
    std::ostream& execCommand(const std::string&, const std::vector< Polygon >&, std::istream&, std::ostream&) const;

  private:
    using Polygons = std::vector< Polygon >;
    using PolygonCommand = std::ostream& (*)(const Polygons& polygons, const Polygon& fig, std::ostream& out);
    using VertCommand = std::ostream& (*)(const Polygons& polygons, const size_t vertexes, std::ostream& out);
    using StateCommand = std::ostream& (*)(const Polygons& polygons, std::ostream& out);

    std::map< std::string, PolygonCommand > polygonCommandDict_;
    std::map< std::string, VertCommand > vertexCommandDict_;
    std::map< std::string, StateCommand > stateCommandDict_;
  };
}
#endif
