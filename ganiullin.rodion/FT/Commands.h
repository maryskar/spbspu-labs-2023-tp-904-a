#ifndef COMMANDS_H
#define COMMANDS_H

#include <iosfwd>
#include "FrequencyDictionary.h"

namespace ganiullin {

  using Dicts = std::unordered_map< std::string, Dict >;
  using SubCommDict = std::unordered_map< std::string, SubComm >;
  using OutS = std::ostream;
  using InS = std::istream;

  class CommandHandler {
  public:
    CommandHandler();
    ~CommandHandler() = default;

    std::string readCommand(InS& in) const;
    OutS& execCommand(const std::string&, Dicts&, InS&, OutS&) const;

  private:
    using InfoFunc = OutS& (*)(OutS&);
    using StateFunc = OutS& (*)(const Dicts&, OutS&);
    using PrintFunc = OutS& (*)(const Dicts&, InS&, OutS&);
    using FuncWithSub = void (*)(Dicts&, const SubCommDict&, InS&, OutS&);
    using OutFileFunc = void (*)(const Dicts&, InS&, OutS&);
    using InFileFunc = void (*)(Dicts&, InS&, OutS&);
    using FuncNoSub = void (*)(Dicts&, InS&, OutS&);

    std::unordered_map< std::string, InfoFunc > infoFuncDict_;
    std::unordered_map< std::string, StateFunc > stateFuncDict_;
    std::unordered_map< std::string, PrintFunc > printFuncDict_;
    std::unordered_map< std::string, FuncWithSub > funcWithSubDict_;
    std::unordered_map< std::string, OutFileFunc > outFileFuncDict_;
    std::unordered_map< std::string, InFileFunc > inFileFuncDict_;
    std::unordered_map< std::string, FuncNoSub > funcNoSubDict_;
    SubCommDict subCommandDict_;
  };
}
#endif
