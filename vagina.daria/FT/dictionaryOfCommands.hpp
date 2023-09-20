#ifndef FT_DICTRIONARYOFCOMMANDS_HPP
#define FT_DICTRIONARYOFCOMMANDS_HPP
#include <map>
#include <string>
#include "commands.hpp"

namespace vagina
{
  class DictionaryOfCommands
  {
    public:
      DictionaryOfCommands();
      std::string readCommand(std::istream& in);
      void doCommand(const std::string& command, const DictionaryOfCommands& commands,
        dictionaryOfNames& dest, std::istream& in, std::ostream& out);
    private:
      void doCommWithoutOutput(const std::string& command, dictionaryOfNames& dict, std::istream& in) const;
      void doCommConstComm(const std::string&, const dictionaryOfNames&, std::istream& in, std::ostream& out) const;
      void doCommNotConst(const std::string&, dictionaryOfNames& dict, std::istream& in, std::ostream& out) const;
      using commandWithoutOutput = void(*)(dictionaryOfNames& dict, std::istream& in);
      using commandConstWithOutput = void(*)(const dictionaryOfNames& dict, std::istream& in, std::ostream& out);
      using commandNotConst = void(*)(dictionaryOfNames& dict, std::istream& in, std::ostream& out);
      std::map< std::string, commandWithoutOutput > withoutOutput;
      std::map< std::string, commandConstWithOutput > constCommand;
      std::map< std::string, commandNotConst > notConstCommand;
  };
}


#endif
