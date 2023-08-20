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
    return static_cast< char >(std::tolower(symbol));
  }
  std::string strFilter(const std::string & str)
  {
    std::string temp;
    std::copy_if(str.begin(), str.end(), std::back_inserter(temp), isLetter);
    std::string result;
    std::transform(temp.begin(), temp.end(), std::back_inserter(result), toLowerCase);
    return result;
  }
  Word::Word(const std::string & str):
  data_(str)
  {
    data_= strFilter(data_);
  }
  bool Word::empty() const
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
    if (!checker)
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
    std::string temp = "";
    in >> temp;
    word.data_ = strFilter(temp);
    return in;
  }
  std::ostream & operator<<(std::ostream & out, const dictionary::value_type & data)
  {
    std::ostream::sentry checker(out);
    if (!checker)
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
