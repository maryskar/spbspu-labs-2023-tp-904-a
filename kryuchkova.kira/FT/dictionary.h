#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <map>
#include <vector>

namespace kryuchkova
{
  class ErDictionary
  {
  public:
    using word = std::string;
    using translations = std::vector< word >;
    ErDictionary(std::map< word, translations > & dict);
  private:
    std::map< word, translations > dict_;
  };

  std::ostream & operator<<(std::ostream & out, const ErDictionary & dict);
  std::istream & operator>>(std::istream & in, ErDictionary & dict);
}

#endif
