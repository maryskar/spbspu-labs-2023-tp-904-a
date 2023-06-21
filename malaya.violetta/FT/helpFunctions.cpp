#include "helpFunctions.hpp"
#include <iostream>
#include <iterator>
#include "commands.hpp"
namespace malaya
{
  Commands::Commands()
  {
    dict1_.insert({"INFO", info});
    dict2_.insert({"MAN", man});
    dict3_.insert({"DELETE_KEY", deleteKey});
    dict3_.insert({"INSERT", insert});
    dict3_.insert({"DELETE_DIT", delDic});
    dict3_.insert({"DO_SYMMETRIC_DIFFERENCE", doSymmetricDifference});
    dict3_.insert({"SUBTRACT", doSubtraction});
    dict3_.insert({"MERGE", merge});
    dict3_.insert({"GET_INTERSECTION", getIntersection});
    dict3_.insert({"INPUT", input});
    dict4_.insert({"SEARCH", search});
    dict4_.insert({"MOST_FREQUENT", mostFreq});
    dict4_.insert({"ARE_SAME", areSame});
    dict4_.insert({"PRINT", print});
    dict4_.insert({"IS_SUBSET", isSubset});
  }
  void Commands::doCommand(const std::string & comm, std::ostream & out)
  {
    auto func = dict1_.at(comm);
    func(out);
  }
  void Commands::doCommand(const std::string & comm, const descriptDict & desc, std::istream & in, std::ostream & out)
  {
    auto func = dict2_.at(comm);
    func(desc, in, out);
  }
  void Commands::doCommand(const std::string & comm, dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    auto func = dict3_.at(comm);
    func(dicts, in, out);
  }
  void Commands::doCommand(const std::string & comm, const dictOfDicts & dicts, std::istream & in, std::ostream & out)
  {
    auto func = dict4_.at(comm);
    func(dicts, in, out);
  }
  std::ostream & printNotFound(std::ostream & out)
  {
    out << "<NOT FOUND>";
    return out;
  }
  std::ostream & printInvalid(std::ostream & out)
  {
    out << "<INVALID COMMAND>";
    return out;
  }
  std::ostream & printYesNo(std::ostream & out, bool number)
  {
    return number ? out << "YES" : out << "NO";
  }
  dictionary & findDict(dictOfDicts & dicts, const std::string & name)
  {
    return dicts.at(name);
  }
  const dictionary & findDict(const dictOfDicts & dicts, const std::string & name)
  {
    return dicts.at(name);
  }

}