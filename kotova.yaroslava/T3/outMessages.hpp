#ifndef OUTMESSAGES_HPP
#define OUTMESSAGES_HPP
#include <map>
#include "geomfigures.hpp"
namespace kotova
{
  std::ostream &outMessageError(std::ostream &out);
  using cmd_out = void (*)(const std::vector< Polygon > &, std::ostream &);
  using cmd_num = void (*)(size_t, const std::vector<Polygon> &, std::ostream &);
  using cmd_fr = void (*)(const std::vector< Polygon > &, std::istream &, std::ostream &);
  using cmd_same = void (*)(const std::vector< Polygon > &, const Polygon &, std::ostream &);
  class CommandDictionary
  {
    public:
      CommandDictionary();
      std::string readCommand(std::istream &in);
      void doCommand(std::string &cmd, std::vector< Polygon > &data,
          const CommandDictionary &cmd_d, std::istream &in, std::ostream &out, const Polygon &pol);
    private:
      std::map<std::string, cmd_out> dict_out;
      std::map<std::string, cmd_num> dict_num;
      std::map<std::string, cmd_fr> dict_fr;
      std::map<std::string, cmd_same> dict_same;
      void doCommandOut(std::string &cmd, const std::vector<Polygon> &polygons, std::ostream &out) const;
      void doCommandNum(std::string &cmd, const std::vector<Polygon> &polygons,
          std::ostream &out, std::size_t n) const;
      void doCommandFr(std::string &cmd, std::vector<Polygon> &polygons, std::ostream &out,
          std::istream &in) const;
      void doCommandSame(std::string &cmd, const std::vector<Polygon> &polygons,
          const Polygon &pol, std::ostream &out) const;
  };
}

#endif
