#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <istream>
#include <ostream>

namespace kryuchkova
{
  class ErDictionary
  {
  public:
    using word = std::string;
    using translations = std::vector< word >;
    ErDictionary();
    ErDictionary(std::string & name);
    ErDictionary(std::string & name, std::map< word, translations > & dict);
    translations find(const word & wrd) const;
    word getName() const;
    void setName(const std::string & name);
    std::map< word, translations > getDict() const;
    void insert(const word & wrd, const translations & trans);
    void erase(const word & wrd);
    size_t size() const;
    void print(const std::ostream & out) const;
  private:
    std::string name_;
    std::map< word, translations > dict_;
  };

  std::ostream & operator<<(std::ostream & out, const ErDictionary & dict);
  std::istream & operator>>(std::istream & in, ErDictionary & dict);
}

#endif
