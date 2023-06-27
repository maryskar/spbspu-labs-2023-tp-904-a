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
    dict3_.insert({"DELETE_DICT", delDic});
    dict3_.insert({"DO_SYMMETRIC_DIFFERENCE", doSymmetricDifference});
    dict3_.insert({"SUBTRACT", doSubtraction});
    dict3_.insert({"MERGE", merge});
    dict3_.insert({"GET_INTERSECTION", getIntersection});
    dict3_.insert({"INPUT", input});
    dict4_.insert({"SEARCH", search});
    dict4_.insert({"FIND_MOST_FREQUENT", mostFreq});
    dict4_.insert({"ARE_SAME", areSame});
    dict4_.insert({"PRINT", print});
    dict4_.insert({"IS_SUBSET", isSubset});
  }
  void Commands::doCommand(const std::string & comm, std::ostream & out) const
  {
    auto func = dict1_.at(comm);
    func(out);
  }
  void Commands::doCommand(const std::string & comm, const descriptDict & desc,
      std::istream & in, std::ostream & out) const
  {
    auto func = dict2_.at(comm);
    func(desc, in, out);
  }
  void Commands::doCommand(const std::string & comm, dictOfDicts & dicts, std::istream & in) const
  {
    auto func = dict3_.at(comm);
    func(dicts, in);
  }
  void Commands::doCommand(const std::string & comm, const dictOfDicts & dicts,
      std::istream & in, std::ostream & out) const
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
  std::string inputCommand(std::istream & in)
  {
    std::string comm = " ";
    in >> comm;
    if (!in)
    {
      throw std::runtime_error("end of stream");
    }
    return comm;
  }
  void executeCommand(dictOfDicts & data, const std::string & comm,
      const descriptDict & descriptions, const Commands & comms, std::ostream & out, std::istream & in)
  {
    try
    {
      comms.doCommand(comm, out);
      return;
    }
    catch (const std::out_of_range & e)
    {}
    try
    {
      comms.doCommand(comm, descriptions, in, out);
      return;
    }
    catch (const std::out_of_range & e)
    {}
    try
    {
      comms.doCommand(comm, data, in);
      return;
    }
    catch (const std::out_of_range & e)
    {}
    comms.doCommand(comm, data, in, out);
  }
  dictionary & findDict(dictOfDicts & dicts, const std::string & name)
  {
    return dicts.at(name);
  }
  const dictionary & findDict(const dictOfDicts & dicts, const std::string & name)
  {
    return dicts.at(name);
  }
  descriptDict makeDescriptDict()
  {
    descriptDict desc;
    desc.insert({"INFO", "gives basic info about all available command"});
    desc.insert({"MAN", "gives info about requested command"});
    desc.insert({"PRINT", "prints the dictionary contents to standard output"});
    desc.insert({"DELETE_DICT", "deletes the requested dictionary"});
    desc.insert({"FIND_MOST_FREQUENT", "prints the most frequent word in requested dictionary"});
    desc.insert({"SEARCH", "searches the word in requested dictionary and "
        "prints it's frequency; if not found, prints the message"});
    desc.insert({"INSERT", "inserts the given key to requested dictionary"});
    desc.insert({"DELETE_KEY", "deletes the given key from requested dictionary"});
    desc.insert({"MERGE", "merges two dictionaries and puts the result to dest dictionary"});
    desc.insert({"GET_INTERSECTION", "intersects two dictionaries and puts the result to dest dictionary"});
    desc.insert({"DO_SYMMETRIC_DIFFERENCE", "finds symmetric difference between two dictionaries "
        "and puts the result to dest dictionary"});
    desc.insert({"SUBTRACT", "subtracts one dictionary from another and puts the result to dest dictionary"});
    desc.insert({"IS_SUBSET", "checks if one dictionary is subset of another"});
    desc.insert({"ARE_SAME", "checks if two dictionaries are identical"});
    desc.insert({"INPUT", "creates new dictionary and fills it with the file contents"});
    return desc;
  }
}
