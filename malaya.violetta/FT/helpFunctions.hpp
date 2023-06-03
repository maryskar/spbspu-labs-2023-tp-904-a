#ifndef FT_HELPFUNCTIONS_HPP
#define FT_HELPFUNCTIONS_HPP
#include <map>
#include <string>
namespace malaya
{
  using dictOfDicts = std::map< std::string, std::map< std::string, size_t > >;
  dictOfDicts readDictionaries(std::istream & in);

}
#endif
