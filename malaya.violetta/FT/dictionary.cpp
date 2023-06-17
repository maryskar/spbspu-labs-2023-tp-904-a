#include "dictionary.hpp"
#include <algorithm>

namespace malaya
{
  bool isLetter(unsigned char symbol)
  {
    return std::isalpha(symbol);
  }
  char toLowerCase(char symbol)
  {
    return std::tolower(symbol);
  }
  std::string strFilter(const std::string & str)
  {
    std::string result = "";
    std::copy_if(str.begin(), str.end(), result.begin(), isLetter);
    std::transform(result.begin(), result.end(), result.begin(), toLowerCase);
    return result;
  }
  Word::Word(std::string str):
  data_(str)
  {
    data_= strFilter(data_);
  }
  bool Word::empty()
  {
    return data_.empty();
  }
  bool operator==(const Word & left, const Word & right)
  {
    return left.data_ == right.data_;
  }
  bool operator<(const Word & left, const Word & right)
  {
    return left.data_ < right.data_;
  }
  std::ostream & operator<<(std::ostream & out, const Word & word)
  {
    std::ostream::sentry checker(out);
    if(!checker)
    {
      return out;
    }
    out << word.data_;
    return out;
  }
  std::istream & operator>>(std::istream & in, Word & word)
  {
    std::istream::sentry checker(in);
    if (!checker)
    {
      return in;
    }
    in >> word.data_;
    return in;
  }
  std::ostream & operator<<(std::ostream & out, const dictionary::value_type & data)
  {
    std::ostream::sentry checker(out);
    if(!checker)
    {
      return out;
    }
    out << data.first << " " << data.second;
    return out;
  }
  bool FrequencyComparator::operator()(const dictionary::value_type & left,
    const dictionary::value_type & right)
  {
    return left.second < right.second;
  }
  bool WordComparator::operator()(const dictionary::value_type & left,
    const dictionary::value_type & right)
  {
    return left.first < right.first;
  }
}