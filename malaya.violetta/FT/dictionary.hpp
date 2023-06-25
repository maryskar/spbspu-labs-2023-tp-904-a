#ifndef FT_DICTIONARY_HPP
#define FT_DICTIONARY_HPP
#include <string>
#include <map>
#include <iostream>

namespace malaya
{
  class Word
  {
   public:
    explicit Word(const std::string & str);
    bool empty() const;
    friend bool operator==(const Word & left, const Word & right);
    friend bool operator<(const Word & left, const Word & right);
    friend std::ostream & operator<<(std::ostream & out, const Word & word);
    friend std::istream & operator>>(std::istream & in, Word & word);
   private:
    std::string data_;
  };
  using dictionary = std::map< Word, size_t >;
  using dictOfDicts = std::map< std::string, dictionary >;
  using descriptDict = std::map< std::string, std::string >;
  std::ostream & operator<<(std::ostream &, const dictionary::value_type &);
  struct FrequencyComparator
  {
    bool operator()(const dictionary::value_type & left, const dictionary::value_type & right);
  };
  struct WordComparator
  {
    bool operator()(const dictionary::value_type & left, const dictionary::value_type & right);
  };
}


#endif
