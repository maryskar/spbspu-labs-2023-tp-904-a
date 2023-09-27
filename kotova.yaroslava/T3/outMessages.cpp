#include "outMessages.hpp"
#include "commands.hpp"
kotova::CommandDictionary::CommandDictionary()
{
  dict_out.insert({"AREA EVEN", areaEven});
  dict_out.insert({"AREA ODD", areaOdd});
  dict_out.insert({"AREA MEAN", areaMean});
  dict_out.insert({"MAX AREA", maxArea});
  dict_out.insert({"MAX VERTEXES", maxVertexes});
  dict_out.insert({"MIN AREA", minArea});
  dict_out.insert({"MIN VERTEXES", minVertexes});
  dict_out.insert({"COUNT EVEN", countEven});
  dict_out.insert({"COUNT ODD", countOdd});
  dict_num.insert({"AREA NUM", areaNumVertexes});
  dict_num.insert({"COUNT NUM", countNumVertexes});
  dict_same.insert({"SAME", isSame});
  dict_fr.insert({"INFRAME", inFrame});
}
std::string kotova::CommandDictionary::readCommand(std::istream &in)
{
  std::string cmd = " ";
  in >> cmd;
  if (!in)
  {
    throw std::runtime_error("Error");
  }
  if (cmd != "SAME" && cmd != "INFRAME")
  {
    std::string cmd2 = " ";
    in >> cmd2;
    if (!in)
    {
      throw std::invalid_argument("Error");
    }
    cmd += " ";
    cmd += cmd2;
  }
  return cmd;
}
void kotova::CommandDictionary::doCommandOut(std::string &cmd, const std::vector<Polygon> &polygons, std::ostream &out) const
{
  auto func = dict_out.at(cmd);
  func(polygons, out);
}
void kotova::CommandDictionary::doCommandNum(std::string &cmd, const std::vector<Polygon> &polygons, std::ostream &out, std::size_t n) const
{
  auto func = dict_num.at(cmd);
  func(n, polygons, out);
}

void kotova::CommandDictionary::doCommandFr(std::string &cmd, std::vector<Polygon> &polygons, std::ostream &out, std::istream &in) const
{
  auto func = dict_fr.at(cmd);
  func(polygons, in, out);
}

void kotova::CommandDictionary::doCommandSame(std::string &cmd, std::vector<Polygon> &polygons, std::ostream &out, std::istream &in) const
{
  auto func = dict_same.at(cmd);
  func(polygons, in, out);
}

void kotova::CommandDictionary::doCommand(std::string &cmd, std::vector< Polygon > &data, const CommandDictionary &cmd_d, std::istream &in, std::ostream &out)
{
  try
  {
    cmd_d.doCommandOut(cmd, data, out);
    return;
  } catch (const std::out_of_range &e)
  {
  }
  try
  {
    cmd_d.doCommandFr(cmd, data, out, in);
    return;
  } catch (const std::out_of_range &e)
  {
  }
  try
  {
    cmd_d.doCommandSame(cmd, data, out, in);
    return;
  } catch (const std::out_of_range &e)
  {
  }
  std::size_t sep = cmd.find(' ');
  std::size_t num = std::stoull(cmd.substr(sep));
  std::string fin_cmd = cmd.substr(0, sep) + " NUM";
  cmd_d.doCommandNum(fin_cmd, data, out, num);
}

