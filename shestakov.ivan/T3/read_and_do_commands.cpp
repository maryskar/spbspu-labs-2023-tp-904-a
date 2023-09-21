#include "read_and_do_commands.h"
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "polygon.h"
#include "commands.h"
#include "auxiliary_commands.h"

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
      {"RMECHO VERT", rmecho},
      {"ECHO VERT",   echo}
    };
  void doConstCmds(const std::vector< Polygon >& polygons, std::ostream& out, const std::string& cmd)
  {
    auto toexecute = const_cmds.at(cmd);
    toexecute(polygons, out);
  }
  void doConstCmdsIn(const std::vector< Polygon >& polygons, size_t vertexes, std::ostream& out, const std::string& cmd)
  {
    auto toexecute = const_cmds_in.at(cmd);
    toexecute(polygons, vertexes, out);
  }
  void doCmdsWithInPolygon(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out, std::string cmd)
  {
    cmd += " VERT";
    auto toexecute = cmds_in.at(cmd);
    toexecute(polygons, in, out);
  }
  void doCommand(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out, std::string cmd)
  {
    if (cmd == "RMECHO" || cmd == "ECHO")
    {
      try
      {
        doCmdsWithInPolygon(polygons, in, out, cmd);
      }
      catch (...)
      {
        printError(out);
      }
    }
    else if (cmd == "COUNT" || cmd == "AREA")
    {
      std::string sub_cmd = "";
      std::getline(in, sub_cmd);
      cmd += sub_cmd;
      if (sub_cmd == " EVEN" || sub_cmd == " ODD" || sub_cmd == " MEAN")
      {
        try
        {
          doConstCmds(polygons, out, cmd);
        }
        catch (...)
        {
          printError(out);
        }
      }
      else
      {
        try
        {
          size_t vert = std::stoull(cmd.substr(' '));
          doConstCmdsIn(polygons, vert, out, cmd);
        }
        catch (...)
        {
          printError(out);
        }
      }
    }
    else
    {
      std::string sub_cmd = "";
      std::getline(in, sub_cmd);
      cmd += sub_cmd;
      try
      {
        doConstCmds(polygons, out, cmd);
      }
      catch (...)
      {
        printError(out);
      }
    }
  }
}
