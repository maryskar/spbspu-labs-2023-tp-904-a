#ifndef COMMANDS_DICTIONARY_H
#define COMMANDS_DICTIONARY_H
#include <map>
#include "commands.h"
namespace mishanina
{
  using vect_pol = std::vector< Polygon >;
  using cmd_out = void (*)(const vect_pol &, std::ostream &);
  using cmd_num = void (*)(const vect_pol &, std::ostream &, std::size_t);
  using cmd_rm = void (*)(vect_pol &, std::ostream &, std::istream &);
  class CommandDictionary
  {
  public:
    CommandDictionary();
    std::string readCommand(std::istream &in);
    void doCommand(vect_pol &pols, std::string &cmd, std::istream &in, std::ostream &out);
  private:
    std::map< std::string, cmd_out > dict_out;
    std::map< std::string, cmd_num > dict_num;
    std::map< std::string, cmd_rm > dict_rm;
    void doCommandOut(std::string &cmd, const vect_pol &pols, std::ostream &out) const;
    void doCommandNum(std::string &cmd, const vect_pol &pols, std::ostream &out, std::size_t num) const;
    void doCommandRm(std::string &cmd, vect_pol &pols, std::ostream &out, std::istream &in) const;
  };
}
#endif
