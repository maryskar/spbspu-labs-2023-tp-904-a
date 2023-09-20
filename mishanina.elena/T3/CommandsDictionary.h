#ifndef COMMANDS_DICTIONARY_H
#define COMMANDS_DICTIONARY_H
#include <map>
#include "commands.h"
namespace mishanina
{
  using vect_pol = std::vector<Polygon>;
  using cmd_out = void (*)(const vect_pol &, std::ostream &);
  class CommandDictionary
  {
  public:
    CommandDictionary();
    void doCommand(vect_pol &pols,
                   std::string &cmd,
                   const CommandDictionary &cmds,
                   std::istream &in,
                   std::ostream &out);
  private:
    std::map<std::string, cmd_out> dict_out;
    void doCommandOut(std::string &cmd, const vect_pol &pols, std::ostream &out) const;
  };
}
#endif
