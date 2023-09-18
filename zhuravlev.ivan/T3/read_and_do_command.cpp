#include "read_and_do_command.hpp"
#include <map>
#include <functional>
#include "sub_commands.hpp"

namespace zhuravlev
{
  using const_cmd_t = std::function< void (const std::vector< zhuravlev::Polygon >, std::ostream&) >;
  //using cmd_t = std::function< void (std::vector< zhuravlev::Polygon >&, std::istream&, std::ostream&) >;
  using cmt_t_with_input = std::function< void (std::vector< zhuravlev::Polygon >&, std::ostream&, const size_t) >;
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
  std::map< std::string, cmt_t_with_input> cmd_with_input
  {
    {"COUNT N", zhuravlev::countVertexes},
    {"AREA N", zhuravlev::AreaVertexes}
  };
  std::string readCommand(std::istream& in)
  {
    std::string command = "";
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      in.setstate(std::ios::failbit);
    }
    std::getline(in, command);
    return command;
  }
  void doCommandWithInput(std::vector< Polygon >& pls, std::ostream& out, const size_t condition, std::string cmd)
  {
    auto toexecute = cmd_with_input.at(cmd);
    toexecute(pls, out, condition);
  }
  void doConstCommand(std::vector< Polygon >& pls, std::ostream& out, std::string cmd)
  {
    auto toexecute = const_cmds.at(cmd);
    toexecute(pls, out);
  }
  void doCommand(std::vector< Polygon >pls, std::ostream& out, std::string command)
  {
    try
    {
      doConstCommand(pls, out, command);
      return;
    }
    catch (const std::runtime_error& e)
    {}
    try
    {
      size_t num = std::stoull(command.substr(command.find_first_of(' ')));
      std::string cmd = (command.substr(0, command.find(' ')) + " N");
      doCommandWithInput(pls, out, num, cmd);
      return;
    }
    catch(const std::runtime_error& e)
    {}
  }
}
