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
    translations find(const word & wrd) const;
    word getName() const;
    void insert(const word & wrd, const translations & trans);
  private:
    std::string name_;
    std::map< word, translations > dict_;
  };


  std::ostream & operator<<(std::ostream & out, const ErDictionary & dict);
  std::istream & operator>>(std::istream & in, ErDictionary & dict);
}

#endif
