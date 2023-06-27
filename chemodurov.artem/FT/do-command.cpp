#include "do-command.hpp"
#include <iostream>

std::string chemodurov::readCommand(std::istream & in)
{
  std::string res;
  in >> res;
  if (!in)
  {
    throw std::runtime_error("End of reading");
  }
  return res;
}

void chemodurov::doCommandFromMaps(const std::string & name_cmd,
    const CommandsMaps & cmds,
    std::istream & in,
    std::ostream & out,
    DictWithFreqDicts & data)
{
  try
  {
    cmds.doCommand(name_cmd, out);
    return;
  }
  catch (const std::out_of_range & e)
  {}
  try
  {
    cmds.doCommand(name_cmd, in, data);
    return;
  }
  catch (const std::out_of_range & e)
  {}
  cmds.doCommand(name_cmd, in, out, data);
}
