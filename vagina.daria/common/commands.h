#ifndef T3_COMMANDS_H
#define T3_COMMANDS_H
#include <map>
#include <polygon.h>

namespace vagina
{
  void messageInvalidCommand(std::ostream& out);
  class DictionaryOfCommands
  {
    public:
      DictionaryOfCommands();
      std::string readCommand(std::istream& in);
      void doCommand(const std::string& command, const DictionaryOfCommands& commands, const std::vector< Polygon >& data,
        std::istream& in, std::ostream& out);
    private:
      void doCommPoly(const std::string& command, const std::vector< Polygon >& data, std::ostream& out) const;
      void doCommVert(const std::string& command, const std::vector< Polygon >& data, std::ostream& out, size_t n) const;
      void doCommPerms(const std::string&, const std::vector< Polygon >&, std::ostream&, std::istream&) const;
      using commandPolygon = void(*)(const std::vector< Polygon >& data, std::ostream& out);
      using commandVertexes = void(*)(const std::vector< Polygon >& data, std::ostream& out, size_t n);
      using commandPerms = void(*)(const std::vector< Polygon >& data, std::ostream& out, std::istream& in);
      std::map< std::string, commandPolygon > polygon;
      std::map< std::string, commandVertexes > vertexes;
      std::map< std::string, commandPerms > permutation;
  };
}

#endif
