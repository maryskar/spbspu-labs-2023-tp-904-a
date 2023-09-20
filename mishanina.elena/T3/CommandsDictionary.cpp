#include "CommandsDictionary.h"
mishanina::CommandDictionary::CommandDictionary()
{
  dict_out.insert({"AREA EVEN", printAreaEven});
  dict_out.insert({"AREA ODD", printAreaOdd});
  dict_out.insert({"AREA MEAN", printAreaMean});
  dict_num.insert({"AREA NUM", printAreaNumOfVertexes});
}
std::string mishanina::CommandDictionary::readCommand(std::istream &in)
{
  std::string cmd = " ";
  in >> cmd;
  if (!in)
  {
    throw std::runtime_error("EOF");
  }
  if (cmd != "RMECHO" && cmd != "RECTS")
  {
    std::string cmd2 = " ";
    in >> cmd2;
    if (!in)
    {
      throw std::invalid_argument("Invalid parameter");
    }
    cmd += " ";
    cmd += cmd2;
  }
  return cmd;
}
void mishanina::CommandDictionary::doCommandOut(std::string &cmd, const vect_pol &pols, std::ostream &out) const
{
  auto func = dict_out.at(cmd);
  func(pols, out);
}
void mishanina::CommandDictionary::doCommandNum(std::string &cmd, const vect_pol &pols, std::ostream &out,
                                                std::size_t num) const
{
  auto func = dict_num.at(cmd);
  func(pols, out, num);
}
void mishanina::CommandDictionary::doCommand(vect_pol &pols, std::string &cmd, const CommandDictionary &cmds,
                                             std::istream &in,
                                             std::ostream &out)
{
  try
  {
    doCommandOut(cmd, pols, out);
    return;
  } catch (const std::out_of_range &e)
  {
  }
}
