#include "read_and_do_command.hpp"
#include <map>
#include <functional>
#include "sub_commands.hpp"

namespace zhuravlev
{
  bool isStringDigit(const std::string& str)
  {
    for (char c : str)
    {
      if (c < '0' || c > '9')
      {
        return false;
      }
    }
    return true;
  }
  using const_cmd_t = std::function< void (const std::vector< zhuravlev::Polygon >&, std::istream&, std::ostream&) >;
  using cmd_t = std::function< void (std::vector< zhuravlev::Polygon >&, std::istream&, std::ostream&) >;
  std::map< std::string, const_cmd_t > const_cmds
  { 
    {"COUNT ODD", zhuravlev::countOdd},
    {"COUNT EVEN", zhuravlev::countEven},
    {"MAX AREA", zhuravlev::MaxArea},
    {"MAX VERTEXES", zhuravlev::MaxVertexes},
    {"AREA MEAN", zhuravlev::AreaMean},
    {"AREA EVEN", zhuravlev::AreaEven},
    {"AREA ODD", zhuravlev::AreaOdd},
    {"AREA", zhuravlev::AreaVertexes},
    {"MIN AREA", zhuravlev::MinArea},
    {"MIN VERTEXES", zhuravlev::MinVertexes},
    {"COUNT", zhuravlev::countVertexes}
  };
  std::map< std::string, cmd_t > cmds
  {
    
  };
  void readAndDoCommand(const std::vector< zhuravlev::Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      in.setstate(std::ios::failbit);
    }
    while (!in.eof())
    {
      std::string cmd;
      in >> cmd;
      if (cmd.empty())
      {
        continue;
      }  
      try
      {
        try
        {
          auto toexecute = const_cmds.at(cmd);
          toexecute(polygons, in, out);
        }
        catch (...)
        {
        }
        auto toexecute = cmds.at(cmd);
        //toexecute(polygons, in, out);
        }
        catch (...)
        {
          zhuravlev::skipUntilNewLines(in);
        }
    }
  }
}
