#ifndef T3_READ_AND_DO_COMMAND_HPP
#define T3_READ_AND_DO_COMMAND_HPP
#include <string>
#include "create-command-dictionary.hpp"

namespace chemodurov
{
  std::string readCommand(std::istream & in);
  void doCommand(const std::string & name_comm,
      const comm_dics_t & commands,
      const std::vector< Polygon > & data,
      std::istream & in,
      std::ostream & out);
}

#endif
