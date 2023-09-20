#ifndef COMMANDS_DICTIONARY_H
#define COMMANDS_DICTIONARY_H
#include <map>
#include "commands.h"
namespace mishanina
{
  using vect_pol = std::vector<Polygon>;
  using cmd_out = void (*)(const vect_pol &, std::ostream &);
  using cmd_num = void (*)(const vect_pol &, std::ostream &, std::size_t);
  class CommandDictionary
  {
  public:
    CommandDictionary();
    std::string readCommand(std::istream &in);
    void doCommand(vect_pol &pols,
                   std::string &cmd,
                   const CommandDictionary &cmds,
                   std::istream &in,
                   std::ostream &out);
  private:
    std::map<std::string, cmd_out> dict_out;
    std::map<std::string, cmd_num> dict_num;
    void doCommandOut(std::string &cmd, const vect_pol &pols, std::ostream &out) const;
    void doCommandNum(std::string &cmd, const vect_pol &pols, std::ostream &out, std::size_t num) const;
  };
}
#endif
