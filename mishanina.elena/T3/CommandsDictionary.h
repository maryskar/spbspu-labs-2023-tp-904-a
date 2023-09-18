#ifndef COMMANDS_DICTIONARY_H
#define COMMANDS_DICTIONARY_H
#include <map>
#include "commands.h"
namespace mishanina{
  using vect_pol = std::vector<Polygon>;
  using commPolygon = void(*)(const vect_pol&, std::ostream&);
  class CommandDictionary {
  public:
    CommandDictionary();
//    ~CommandDictionary() = default;
//    std::string inputCommand(std::istream& in);
    void doCommand(
      vect_pol& pols,
      std::string& cmd,
      const CommandDictionary& cmds,
      std::istream& in,
      std::ostream& out
    );
  private:
    std::map< std::string, commPolygon > dict_pol;
//    std::map< std::string, commVertex > dict_ver;
//    std::map< std::string, commRmecho > dict_rm;
    void doCommandPol(std::string& cmd, const vect_pol& pols, std::ostream& out) const;
//    void doCommandVer(std::string& cmd, const vect_pol& pols, std::ostream& out, size_t num) const;
//    void doCommandRm(std::string& cmd, vect_pol& pols, std::ostream& out, std::istream& in) const;
  };
}
#endif
