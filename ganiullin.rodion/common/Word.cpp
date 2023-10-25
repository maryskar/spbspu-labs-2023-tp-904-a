#include "Word.h"

#include <iostream>

#include "TypesIO.h"

using Word = ganiullin::Word;

Word::Word(const std::string& str)
    : str_(str)
{
}
std::istream& ganiullin::operator>>(std::istream& in, Word& word)
{

  std::string str;
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  in >> str;
  char a = '\0';
  a = str.at(0);
  while (!isalnum(a) && a != '\0') {
    str.erase(0, 1);
    a = str.at(0);
  }
  a = str.at(str.size() - 1);
  while (!isalnum(a) && a != '\0') {
    str.erase(str.size() - 1, 1);
    a = str.at(str.size() - 1);
  }

  str.shrink_to_fit();
  for (size_t i = 0; i < str.size(); i++) {
    str[i] = std::tolower(str[i]);
  }

  word.str_ = str;
  return in;
}
std::ostream& ganiullin::operator<<(std::ostream& out, const Word& word)
{
  return out << word.str_;
}
bool ganiullin::operator<(const Word& lhs, const Word& rhs)
{
  return lhs.str_ < rhs.str_;
}
const std::string& Word::get() const
{
  return str_;
}
bool Word::empty() const
{
  return str_.empty();
}
bool ganiullin::operator==(const Word& lhs, const Word& rhs)
{
  return lhs.str_ == rhs.str_;
}

size_t std::hash< Word >::operator()(const Word& word) const
{
  return std::hash< std::string > {}(word.get());
}
