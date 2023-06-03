#ifndef FT_HELPFUNCTIONS_HPP
#define FT_HELPFUNCTIONS_HPP
#include <map>
#include <string>
namespace malaya
{
  using dictionary = std::map< std::string, size_t >;
  using dictOfDicts = std::map< std::string, dictionary >;
  dictOfDicts readDictionaries(std::istream & in);
  using oneDictFunc = void(*)(dictionary &, const std::string & first);
  using twoDictFunc = void(*)(dictionary &, const std::string & first,
    const std::string & second, std::ostream & out);
  using threeDictFunc = void(*)(const dictionary &, const dictionary &,
    const dictionary &, std::ostream & out);
  using manFunc = void(*)(const std::string & command, std::ostream & out);
  using deleteFunc = void(*)(dictOfDicts &, const std::string &);
  struct commands
  {
    std::map< std::string, void(*)(std::ostream & out) > dict1;
    std::map< std::string, manFunc > dict2;
    std::map< std::string, threeDictFunc > dict3;
    std::map< std::string, twoDictFunc > dict4;
    std::map< std::string, oneDictFunc > dict5;
    std::map< std::string, deleteFunc > dict6;
  };
  commands makeCommandsDictionaries();
}
#endif
