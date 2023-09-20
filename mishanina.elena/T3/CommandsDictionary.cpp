#include "CommandsDictionary.h"
mishanina::CommandDictionary::CommandDictionary()
{
  dict_out.insert({"AREA EVEN", printAreaEven});
  dict_out.insert({"AREA ODD", printAreaOdd});
  dict_out.insert({"AREA MEAN", printAreaMean});
}
void mishanina::CommandDictionary::doCommandOut(std::string &cmd, const vect_pol &pols, std::ostream &out) const
{
  auto func = dict_out.at(cmd);
  func(pols, out);
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
