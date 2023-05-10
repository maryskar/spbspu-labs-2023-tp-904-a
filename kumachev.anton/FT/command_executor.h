#ifndef FT_COMMAND_EXECUTOR_H
#define FT_COMMAND_EXECUTOR_H

#include <iosfwd>
#include <string>
#include <limits>
#include "program_state.h"
#include "english_russian_dictionary.h"

namespace kumachev {
  class CommandExecutor {
  public:
    CommandExecutor(std::istream &istream, std::ostream &ostream, kumachev::State &state, bool interactive);
    CommandExecutor(const CommandExecutor &rhs) = delete;
    void execute();

  private:
    using command = void (*)(CommandExecutor& executor);

    void process(std::string &&cmd);
    static void processHelp(CommandExecutor &executor);
    static void processDicts(CommandExecutor &executor);
    static void processCreate(CommandExecutor &executor);
    static void processLoad(CommandExecutor &executor);
    static void processSave(CommandExecutor &executor);
    static void processSaveOverwrite(CommandExecutor &executor);
    static void processAdd(CommandExecutor &executor);
    static void processClear(CommandExecutor &executor);
    static void processTranslate(CommandExecutor &executor);
    static void processExecute(CommandExecutor &executor);
    static void processMerge(CommandExecutor &executor);
    static void processSubtract(CommandExecutor &executor);

    std::istream &istream_;
    std::ostream &ostream_;
    kumachev::State &state_;
    const bool interactive_;
    std::map<std::string, command> commands_;

    static constexpr auto SKIP_MAX = std::numeric_limits< std::streamsize >::max();
  };
}

#endif //FT_COMMAND_EXECUTOR_H
