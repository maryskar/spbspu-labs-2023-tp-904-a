#include "read_and_do_command.hpp"
#include <map>
#include <functional>
#include "sub_commands.hpp"

namespace zhuravlev
{
  std::string readCommand(std::istream& in)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      throw std::runtime_error("EOF");
    }
    std::string command = "";
    in >> command;
    if (command != "INFRAME" && command != "RMECHO")
    {
      std::string param = "";
      in >> param;
      if (!in)
      {
        throw std::invalid_argument("Invalid parameter");
      }
      command += " ";
      command += param;
    }
    return command;
  }
  void doCommandWithInput(std::vector< Polygon >& pls, std::ostream& out, const size_t condition, std::string cmd)
  {
    using cmt_t_with_input = std::function< void (std::vector< zhuravlev::Polygon >&, std::ostream&, const size_t) >;
    std::map< std::string, cmt_t_with_input> cmd_with_input
    {
      {"COUNT N", zhuravlev::countVertexes},
      {"AREA N", zhuravlev::AreaVertexes}
    };
    auto toexecute = cmd_with_input.at(cmd);
    toexecute(pls, out, condition);
  }
  void doConstCommand(std::vector< Polygon >& pls, std::ostream& out, std::string cmd)
  {
    using const_cmd_t = std::function< void (const std::vector< zhuravlev::Polygon >, std::ostream&) >;
    std::map< std::string, const_cmd_t > const_cmds
    {
      {"COUNT ODD", zhuravlev::countOdd},
      {"COUNT EVEN", zhuravlev::countEven},
      {"MAX AREA", zhuravlev::MaxArea},
      {"MAX VERTEXES", zhuravlev::MaxVertexes},
      {"AREA MEAN", zhuravlev::AreaMean},
      {"AREA EVEN", zhuravlev::AreaEven},
      {"AREA ODD", zhuravlev::AreaOdd},
      {"MIN AREA", zhuravlev::MinArea},
      {"MIN VERTEXES", zhuravlev::MinVertexes},
    };
    auto toexecute = const_cmds.at(cmd);
    toexecute(pls, out);
  }
  void doCommandWithInputPolygon(std::vector< Polygon >& pls, std::istream& in, std::ostream& out, std::string cmd)
  {
    using cmd_t_with_input_polygon = std::function< void (std::vector< zhuravlev::Polygon >&, std::istream& in, std::ostream&) >;
    std::map< std::string, cmd_t_with_input_polygon > cmds_with_input_polygon
    {
      {"INFRAME", zhuravlev::inFrame},
      {"RMECHO", zhuravlev::rmEcho}
    };
    auto toexecute = cmds_with_input_polygon.at(cmd);
    toexecute(pls, in, out);
  }
  void doCommand(std::vector< Polygon >pls, std::istream& in, std::ostream& out, std::string command)
  {
    try
    {
      doConstCommand(pls, out, command);
      return;
    }
    catch (const std::out_of_range& e)
    {}
    try
    {
      size_t num = std::stoull(command.substr(command.find_first_of(' ')));
      std::string cmd = (command.substr(0, command.find(' ')) + " N");
      doCommandWithInput(pls, out, num, cmd);
      return;
    }
    catch (const std::out_of_range& e)
    {}
    try
    {
      doCommandWithInputPolygon(pls, in, out, command);
      return;
    }
    catch (const std::out_of_range& e)
    {}
  }
}
