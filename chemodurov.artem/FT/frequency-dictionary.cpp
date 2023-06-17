#include "frequency-dictionary.hpp"
#include <iostream>
#include <algorithm>

namespace chemodurov
{
  bool isAlphabet(char c)
  {
    return std::isalpha(static_cast< unsigned char >(c));
  }

  char toLower(char c)
  {
    return static_cast< char >(std::tolower(c));
  }

  Word::Word(const std::string & str_word):
   data_(str_word)
  {
    auto it = std::find_if(data_.begin(), data_.end(), isAlphabet);
    data_.erase(data_.begin(), it);
    auto rit = std::find_if(data_.rbegin(), data_.rend(), isAlphabet);
    data_.erase(rit.base(), data_.end());
    if (!data_.empty() && !isAlphabet(data_[0]))
    {
      data_.erase(0, 1);
    }
    if (data_.empty())
    {
      throw std::invalid_argument("Empty word");
    }
    std::transform(data_.begin(), data_.end(), data_.begin(), toLower);
  }

  std::string Word::getWord() const
  {
    return data_;
  }

  bool operator<(const Word & lhs, const Word & rhs)
  {
    return lhs.getWord() < rhs.getWord();
  }

  std::ostream & operator<<(std::ostream & out, const chemodurov::Word & word)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    return out << word.getWord();
  }

  ios::SpecialDataIO::SpecialDataIO(const std::pair< const Word, size_t > & pair):
   pair_(pair)
  {}

  const std::pair< const Word, size_t > & ios::SpecialDataIO::getData() const
  {
    return pair_;
  }

  std::ostream & ios::operator<<(std::ostream & out, ios::SpecialDataIO data)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    const auto & pair = data.getData();
    return out << pair.first << ' ' << pair.second;
  }
}
