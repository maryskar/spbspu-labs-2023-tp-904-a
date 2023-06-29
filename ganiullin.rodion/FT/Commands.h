#ifndef COMMANDS_H
#define COMMANDS_H

#include <iosfwd>
#include "FrequencyDictionary.h"

namespace ganiullin {

  using DictOfFreqDicts = std::unordered_map< std::string, FreqDict >;
  using SubCommandDict = std::unordered_map< std::string, SubCommand >;

  class CommandHandler {
  public:
    CommandHandler();
    ~CommandHandler() = default;

    std::string readCommand(std::istream& in) const;
    std::ostream& execCommand(const std::string&, DictOfFreqDicts&, std::istream&,
        std::ostream&) const;

  private:
    using InfoFunc = std::ostream& (*)(std::ostream&);
    using StateFunc = std::ostream& (*)(const DictOfFreqDicts&, std::ostream&);
    using PrintFunc = std::ostream& (*)(const DictOfFreqDicts&, std::istream&, std::ostream&);
    using FuncWithSub = void (*)(DictOfFreqDicts&, const SubCommandDict&, std::istream&,
        std::ostream&);
    using OutFileFunc = void (*)(const DictOfFreqDicts&, std::istream&, std::ostream&);
    using InFileFunc = void (*)(DictOfFreqDicts&, std::istream&, std::ostream&);
    using FuncNoSub = void (*)(DictOfFreqDicts&, std::istream&, std::ostream&);

    std::unordered_map< std::string, InfoFunc > infoFuncDict_;
    std::unordered_map< std::string, StateFunc > stateFuncDict_;
    std::unordered_map< std::string, PrintFunc > printFuncDict_;
    std::unordered_map< std::string, FuncWithSub > funcWithSubDict_;
    std::unordered_map< std::string, OutFileFunc > outFileFuncDict_;
    std::unordered_map< std::string, InFileFunc > inFileFuncDict_;
    std::unordered_map< std::string, FuncNoSub > funcNoSubDict_;
    SubCommandDict subCommandDict_;
  };
}
#endif
