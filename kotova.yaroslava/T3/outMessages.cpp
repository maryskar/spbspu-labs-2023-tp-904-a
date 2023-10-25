#include "outMessages.hpp"
#include <IO_structs.hpp>
#include "commands.hpp"

std::ostream &kotova::outMessageError(std::ostream &out)
{
  out << "<INVALID COMMAND>";
  return out;
}

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
void kotova::CommandDictionary::doCommandOut(const std::string &cmd, const std::vector<Polygon> &polygons,
    std::ostream &out) const
{
  auto func = dict_out.at(cmd);
  func(polygons, out);
}
void kotova::CommandDictionary::doCommandNum(std::size_t n, const std::string &cmd, const std::vector<Polygon> &polygons,
    std::ostream &out) const
{
  auto func = dict_num.at(cmd);
  func(n, polygons, out);
}

void kotova::CommandDictionary::doCommandS(const std::string &cmd, const std::vector<Polygon> &polygons, const Polygon &pol,
    std::ostream &out) const
{
  auto func = dict_same.at(cmd);
  func(polygons, pol, out);
}

void kotova::CommandDictionary::doCommandFr(const std::string &cmd, const Polygon &pol, std::ostream &out) const
{
  auto func = dict_fr.at(cmd);
  func(pol, out);
}

void kotova::CommandDictionary::doCommand(const std::string &cmd, const std::vector< Polygon > &polygons,
    const CommandDictionary &cmd_dict, std::istream &in, std::ostream &out)
{
  if (cmd == "SAME" || cmd == "INFRAME")
  {
    Polygon data;
    in >> data >> DelimiterIO{'\n'};
    if (!in)
    {
      throw std::invalid_argument("error");
    }
    try
    {
      cmd_dict.doCommandFr(cmd, data, out);
      return;
    }
    catch(const std::out_of_range &e)
    {
    }
    try
    {
      cmd_dict.doCommandS(cmd, polygons, data, out);
      return;
    }
    catch (const std::out_of_range &e)
    {
    }
  }
  try
  {
    cmd_dict.doCommandOut(cmd, polygons, out);
    return;
  }
  catch (const std::out_of_range &e)
  {
  }
  size_t sep = cmd.find(' ');
  size_t num = std::stoull(cmd.substr(sep));
  std::string fin_cmd = cmd.substr(0, sep) + " NUM";
  cmd_dict.doCommandNum(num, fin_cmd, polygons, out);
}

