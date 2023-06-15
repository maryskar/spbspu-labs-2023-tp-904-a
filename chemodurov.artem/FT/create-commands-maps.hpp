#ifndef FA_CREATE_COMMANDS_MAPS_HPP
#define FA_CREATE_COMMANDS_MAPS_HPP
#include "frequency-dictionary.hpp"

namespace chemodurov
{
  class CommandsMaps
  {
   public:
    CommandsMaps();
    void doCommand(const std::string & name_cmd, std::ostream & out) const;
    void doCommand(const std::string & name_cmd, std::istream & in, DictWithFreqDicts & data) const;
    void doCommand(const std::string & name_cmd, std::istream & in, std::ostream & out, const DictWithFreqDicts & data) const;
   private:
    using fst_cmd_t = void(*)(std::ostream &);
    using snd_cmd_t = void(*)(std::istream &, DictWithFreqDicts &);
    using trd_cmd_t = void(*)(std::istream &, std::ostream &, const DictWithFreqDicts &);
    std::map< std::string, fst_cmd_t > fst_map_;
    std::map< std::string, snd_cmd_t > snd_map_;
    std::map< std::string, trd_cmd_t > trd_map_;
  };

  std::ostream & outEmpty(std::ostream & out);
  std::ostream & outInvalidCommand(std::ostream & out);
}

#endif
