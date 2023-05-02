#ifndef FT_COMMAND_EXECUTOR_H
#define FT_COMMAND_EXECUTOR_H

#include <istream>
#include <string>
#include "program_state.h"

namespace kumachev {
  class CommandExecutor {
  public:
    CommandExecutor(std::istream &istream, kumachev::State &state);
    CommandExecutor(const CommandExecutor &rhs) = delete;
    void execute();

  private:
    void process(std::string &&cmd);

    std::istream &istream_;
    kumachev::State &state_;
  };
}


#endif //FT_COMMAND_EXECUTOR_H
