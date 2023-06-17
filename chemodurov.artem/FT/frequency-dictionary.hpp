#ifndef FA_FREQUENCY_DICTIONARY_HPP
#define FA_FREQUENCY_DICTIONARY_HPP
#include <map>

namespace chemodurov
{
  class Word
  {
   public:
    explicit Word(const std::string & str_word);
    std::string getWord() const;
   private:
    std::string data_;
  };
  bool operator<(const Word & lhs, const Word & rhs);
  std::ostream & operator<<(std::ostream & out, const Word & word);
  namespace ios
  {
    class SpecialDataIO
    {
     public:
      SpecialDataIO(const std::pair< const Word, size_t > & pair);
      const std::pair< const Word, size_t > & getData() const;
     private:
      const std::pair< const Word, size_t > & pair_;
    };
    std::ostream & operator<<(std::ostream & out, SpecialDataIO pair);
  }
  using FreqDict = std::map< Word, size_t >;
  using DictWithFreqDicts = std::map< std::string, FreqDict >;
}

#endif
