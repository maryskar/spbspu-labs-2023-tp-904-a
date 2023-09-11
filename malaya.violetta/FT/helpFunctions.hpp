#ifndef FT_HELPFUNCTIONS_HPP
#define FT_HELPFUNCTIONS_HPP
#include <map>
#include <string>
#include <iosfwd>
#include "dictionary.hpp"
namespace malaya
{
  std::ostream & printNotFound(std::ostream & out);
  std::ostream & printInvalid(std::ostream & out);
  std::ostream & printYesNo(std::ostream & out, bool number);
  descriptDict makeDescriptDict();
  std::string inputCommand(std::istream & in);
  dictionary & findDict(dictOfDicts &, const std::string & name);
  const dictionary & findDict(const dictOfDicts & dicts, const std::string & name);
  class Commands
  {
   public:
    Commands();
    void doCommand(const std::string & comm, std::ostream & out) const;
    void doCommand(const std::string & comm, const descriptDict &, std::istream &, std::ostream &) const;
    void doCommand(const std::string & comm, dictOfDicts &, std::istream &) const;
    void doCommand(const std::string & comm, const dictOfDicts &, std::istream &, std::ostream &) const;
   private:
    using firstFunc = void(*)(const descriptDict &, std::istream &, std::ostream &);
    using secondFunc = void(*)(dictOfDicts &, std::istream &);
    using thirdFunc = void(*)(const dictOfDicts &, std::istream &, std::ostream &);
    std::map< std::string, void(*)(std::ostream & out) > dict1_;
    std::map< std::string, firstFunc > dict2_;
    std::map< std::string, secondFunc > dict3_;
    std::map< std::string, thirdFunc > dict4_;
  };
  void executeCommand(dictOfDicts &, const std::string &, const descriptDict &,
      const Commands &, std::ostream & out, std::istream & in);
}
#endif
