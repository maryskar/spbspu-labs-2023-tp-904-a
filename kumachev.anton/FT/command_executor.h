#ifndef FT_COMMAND_EXECUTOR_H
#define FT_COMMAND_EXECUTOR_H

#include <iosfwd>
#include <string>
#include <limits>
#include <unordered_map>
#include "program_state.h"

namespace kumachev {
  using string_vector = std::vector< std::string >;
  using command_handler = void (*)(State &state, string_vector &args,
      std::ostream &ostream);

  struct CommandSystem {
    std::unordered_map< std::string, command_handler > handlers;
  };

  class CommandExecutor {
  public:
    CommandExecutor(std::istream &istream, std::ostream &ostream,
        const CommandSystem& commandSystem, kumachev::State &state);

    void handleCommand();

  private:
    std::istream &istream_;
    std::ostream &ostream_;
    const CommandSystem &commandSystem_;
    State &state_;
  };

  CommandSystem createCommandSystem();
}

#endif //FT_COMMAND_EXECUTOR_H
