#ifndef OUTMESSAGES_HPP
#define OUTMESSAGES_HPP
#include <map>
#include <IO_structs.hpp>
#include "geomfigures.hpp"
namespace kotova
{
  std::ostream &outMessageError(std::ostream &out);
  using cmd_out = void (*)(const std::vector< Polygon > &, std::ostream &);
  using cmd_num = void (*)(size_t, const std::vector< Polygon > &, std::ostream &);
  using cmd_same = void (*)(const std::vector< Polygon > &, const Polygon &, std::ostream &);
  using cmd_fr = void (*)(const Polygon &, std::ostream &);
  class CommandDictionary
  {
    public:
      CommandDictionary();
      std::string readCommand(std::istream &in);
      void doCommand(const std::string &cmd, const std::vector< Polygon > &polygons,
          const CommandDictionary &cmd_dict, std::istream &in, std::ostream &out);
    private:
      std::map< std::string, cmd_out > dict_out;
      std::map< std::string, cmd_num > dict_num;
      std::map< std::string, cmd_same > dict_same;
      std::map< std::string, cmd_fr > dict_fr;
      void doCommandOut(const std::string &cmd, const std::vector< Polygon > &polygons, std::ostream &out) const;
      void doCommandNum(std::size_t n, const std::string &cmd, const std::vector< Polygon > &polygons,
          std::ostream &out) const;
      void doCommandS(const std::string &cmd, const std::vector< Polygon > &polygons, const Polygon &pol,
          std::ostream &out) const;
      void doCommandFr(const std::string &cmd, const Polygon &pol, std::ostream &out) const;
  };
}

#endif
