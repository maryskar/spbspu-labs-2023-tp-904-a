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
  dictionary & findDict(dictOfDicts &, const std::string & name);
  const dictionary & findDict(const dictOfDicts & dicts, const std::string & name);
  class Commands
  {
   public:
    Commands();
    void doCommand(const std::string & comm, std::ostream & out);
    void doCommand(const std::string & comm, const descriptDict &, std::istream &, std::ostream &);
    void doCommand(const std::string & comm, dictOfDicts &, std::istream &, std::ostream &);
    void doCommand(const std::string & comm, const dictOfDicts &, std::istream &, std::ostream &);
   private:
    using firstFunc = void(*)(const descriptDict &, std::istream &, std::ostream &);
    using secondFunc = void(*)(dictOfDicts &, std::istream &, std::ostream &);
    using thirdFunc = void(*)(const dictOfDicts &, std::istream &, std::ostream &);
    std::map< std::string, void(*)(std::ostream & out) > dict1_;
    std::map< std::string, firstFunc > dict2_;
    std::map< std::string, secondFunc > dict3_;
    std::map< std::string, thirdFunc > dict4_;
  };
}
#endif
