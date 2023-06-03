#ifndef FT_HELPFUNCTIONS_HPP
#define FT_HELPFUNCTIONS_HPP
#include <map>
#include <string>
#include <iosfwd>
namespace malaya
{
  void printNotFound(std::ostream & out);
  void printInvalid(std::ostream & out);
  using dictionary = std::map< std::string, size_t >;
  using dictOfDicts = std::map< std::string, dictionary >;
  dictOfDicts readDictionaries(std::istream & in); //реализовать
  dictionary & findDict(dictOfDicts &, const std::string & name);
  using oneDictFunc = void(*)(dictOfDicts &, const std::string & first,
    std::ostream & out);
  using twoDictFunc = void(*)(dictOfDicts &, const std::string & first,
    const std::string & second, std::ostream & out);
  using threeDictFunc = void(*)(dictOfDicts &, const std::string & first,
    const std::string & second, const std::string & third, std::ostream & out);
  using manFunc = void(*)(const std::string & command, std::ostream & out); //должен принимать словарь команд с описаниями
  struct commands
  {
    std::map< std::string, void(*)(std::ostream & out) > dict1;
    std::map< std::string, manFunc > dict2;
    std::map< std::string, threeDictFunc > dict3;
    std::map< std::string, twoDictFunc > dict4;
    std::map< std::string, oneDictFunc > dict5;
  };
  commands makeCommandsDictionaries(); //реализовать
}
#endif
