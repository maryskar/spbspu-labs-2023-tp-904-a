#include "read_and_do_commands.h"
#include <functional>
#include <map>
#include "commands.h"

namespace shestakov
{
  using const_cmd_t = std::function< void(const std::vector < Polygon >&, std::ostream&) >;
  using const_cmd_t_in = std::function< void(const std::vector < Polygon >&, size_t, std::ostream&) >;
  using cmd_t = std::function< void(std::vector < Polygon >&, std::istream&, std::ostream&) >;
  std::map <std::string, const_cmd_t> const_cmds
    {
      {"AREA EVEN",    areaEven},
      {"AREA ODD",     areaOdd},
      {"AREA MEAN",    areaMean},
      {"MAX AREA",     maxArea},
      {"MAX VERTEXES", maxVertexes},
      {"MIN AREA",     minArea},
      {"MIN VERTEXES", minVertexes},
      {"COUNT EVEN",   countEven},
      {"COUNT ODD",    countOdd}
    };
  std::map <std::string, const_cmd_t_in> const_cmds_in
    {
      {"COUNT", countVert},
      {"AREA",  areaVert}
    };
  std::map <std::string, cmd_t> cmds_in
    {
      {"RMECHO", rmecho},
      {"ECHO",   echo}
    };
  std::string readCommand(std::istream& in)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      throw std::runtime_error("EOF");
    }
    std::string cmd = "";
    in >> cmd;
    if (const_cmds.find(cmd) == const_cmds.end() && const_cmds_in.find(cmd) == const_cmds_in.end() && cmds_in.find(cmd) == cmds_in.end())
    {
      throw std::logic_error("There is no such command");
    }
    if (cmd != "ECHO" && cmd != "RMECHO" && (cmd == "MAX" || cmd == "MIN" || cmd == "AREA" || cmd == "COUNT"))
    {
      std::string param = "";
      in >> param;
      if (!in)
      {
        throw std::invalid_argument("Invalid parameter");
      }
      cmd += " ";
      cmd += param;
    }
    return cmd;
  }
  void doConstCmds(const std::vector< Polygon >& polygons, std::ostream& out, const std::string& cmd)
  {
    auto toexecute = const_cmds.at(cmd);
    toexecute(polygons, out);
  }
  void doConstCmdsIn(const std::vector< Polygon >& polygons, std::ostream& out, std::string cmd)
  {
    size_t vertexes = std::stoull(cmd.substr(cmd.find_first_of(' ')));
    cmd = cmd.substr(0, cmd.find(' '));
    if (vertexes < 3)
    {
      throw std::invalid_argument("Invalid arguments");
    }
    auto toexecute = const_cmds_in.at(cmd);
    toexecute(polygons, vertexes, out);
  }
  void doCmdsWithInPolygon(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out, const std::string& cmd)
  {
    auto toexecute = cmds_in.at(cmd);
    toexecute(polygons, in, out);
  }
  void doCommand(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out, std::string cmd)
  {
    try
    {
      doConstCmds(polygons, out, cmd);
      return;
    }
    catch (const std::out_of_range& e)
    {}
    try
    {
      doCmdsWithInPolygon(polygons, in, out, cmd);
      return;
    }
    catch (const std::out_of_range& e)
    {}
    try
    {
      doConstCmdsIn(polygons, out, cmd);
      return;
    }
    catch (const std::out_of_range& e)
    {}
  }
}
