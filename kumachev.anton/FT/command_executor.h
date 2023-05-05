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
    using Dictionary = EnglishRussianDictionary< std::map< std::string, std::vector< std::string > > >;
    CommandExecutor(std::istream &istream, std::ostream &ostream, kumachev::State &state, bool interactive);
    CommandExecutor(const CommandExecutor &rhs) = delete;
    void execute();

  private:
    void process(std::string &&cmd);
    void processHelp();
    void processDicts();
    void processCreate(std::string &&cmd);
    void processLoad(std::string &&cmd);
    void processSave(std::string &&cmd);
    void processSaveOverwrite(std::string &&cmd);
    void processAdd(std::string &&cmd);
    void processClear(std::string &&cmd);
    void processTranslate(std::string &&cmd);
    void processExecute(std::string &&cmd);
    void processMerge(std::string &&cmd);
    void processSubtract(std::string &&cmd);

    std::istream &istream_;
    std::ostream &ostream_;
    kumachev::State &state_;
    const bool interactive_;

    static constexpr auto SKIP_MAX = std::numeric_limits< std::streamsize >::max();
  };
}

#endif //FT_COMMAND_EXECUTOR_H
