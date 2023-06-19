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
   //СДЕЛАТЬ ФУНКЦИЮ ДЛЯ ЗАПОЛНЕНИЯ
  dictOfDicts readDictionaries(std::istream & in); //реализовать
  dictionary & findDict(dictOfDicts &, const std::string & name);
  using firstFunc = void(*)(const descriptDict &, std::istream &, std::ostream &);
  using secondFunc = void(*)(dictOfDicts &, std::istream &, std::ostream &);
  class Commands
  {
   public:
    Commands();
    void doCommand(std::ostream & out);
    void doCommand(const descriptDict &, std::istream &, std::ostream &);
    void doCommand(dictOfDicts &, std::istream &, std::ostream &);
   private:
    std::map< std::string, void(*)(std::ostream & out) > dict1_;
    std::map< std::string, firstFunc > dict2_;
    std::map< std::string, secondFunc > dict3_;
  };
}
#endif
