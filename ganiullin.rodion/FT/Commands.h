#ifndef COMMANDS_OLD_H
#define COMMANDS_OLD_H

#include <iosfwd>

#include "FrequencyDictionary.h"

namespace ganiullin {

  using Dicts = std::unordered_map< std::string, FreqDict >;
  using SubCommDict = std::unordered_map< std::string, SubComm >;

  class CommandHandler {
  public:
    CommandHandler(std::istream& in, std::ostream& out);
    ~CommandHandler() = default;

    std::string readCommand() const;
    std::ostream& execCommand(const std::string&, Dicts&);

  private:
    void help();

    void listDicts(const Dicts& dicts);
    void printDict(const Dicts& dicts);
    void printCommon(const Dicts& dicts);
    void printRare(const Dicts& dicts);
    void printElem(const Dicts& dicts);
    void saveDicts(const Dicts& dicts);

    void getUnion(Dicts& dicts);
    void getIntersection(Dicts& dicts);
    void getDiff(Dicts& dicts);
    void loadDicts(Dicts& dicts);
    void readIntoDict(Dicts& dicts);

    using InfoFunc = void (ganiullin::CommandHandler::*)();
    using ConstFunc = void (ganiullin::CommandHandler::*)(const Dicts&);
    using NonConstFunc = void (ganiullin::CommandHandler::*)(Dicts&);

    std::istream& comIn_;
    std::ostream& comOut_;
    std::unordered_map< std::string, InfoFunc > infoFuncDict_;
    std::unordered_map< std::string, ConstFunc > constFuncDict_;
    std::unordered_map< std::string, NonConstFunc > nonConstFuncDict_;
    SubCommDict subCommandDict_;
  };
}
#endif
