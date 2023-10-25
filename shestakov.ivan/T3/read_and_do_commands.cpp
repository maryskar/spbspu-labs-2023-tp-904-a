#include "read_and_do_commands.h"
#include <functional>
#include <map>
#include "commands.h"

namespace shestakov
{
  using const_cmd_t = std::function< void(const std::vector < Polygon >&, std::ostream&) >;
  using const_cmd_t_in = std::function< void(const std::vector < Polygon >&, size_t, std::ostream&) >;
  using cmd_t = std::function< void(std::vector < Polygon >&, std::istream&, std::ostream&) >;
  std::string readCommand(std::istream& in)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      throw std::runtime_error("EOF");
    }
    std::string cmd = "";
    in >> cmd;
    return cmd;
  }
  void doConstCmds(const std::vector< Polygon >& polygons, std::ostream& out, const std::string& cmd)
  {
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
    auto toexecute = const_cmds.at(cmd);
    toexecute(polygons, out);
  }
  void doConstCmdsIn(const std::vector< Polygon >& polygons, std::ostream& out, std::string cmd)
  {
    std::map <std::string, const_cmd_t_in> const_cmds_in
      {
        {"COUNT", countVert},
        {"AREA",  areaVert}
      };
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
    std::map <std::string, cmd_t> cmds_in
      {
        {"RMECHO", rmecho},
        {"ECHO",   echo}
      };
    auto toexecute = cmds_in.at(cmd);
    toexecute(polygons, in, out);
  }
  void doCommand(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out, std::string cmd)
  {
    try
    {
      doCmdsWithInPolygon(polygons, in, out, cmd);
      return;
    }
    catch (const std::out_of_range& e)
    {}
    try
    {
      std::string sub_cmd = "";
      std::cin >> sub_cmd;
      cmd += " " + sub_cmd;
      doConstCmds(polygons, out, cmd);
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
