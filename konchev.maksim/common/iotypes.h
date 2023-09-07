#ifndef KONCHEV_MAKSIM_IOTYPES_H
#define KONCHEV_MAKSIM_IOTYPES_H
#include <string>
#include <fstream>
namespace konchev
{
  struct delimiter
  {
    char exp;
  };
  struct label
  {
    std::string str;
  };
  struct LongLong
  {
    long long &ref;
  };
  struct uLongLong
  {
    unsigned long long &ref;
  };
  struct String
  {
    std::string &ref;
  };
  std::istream &operator>>(std::istream &in, delimiter &&data);
  std::istream &operator>>(std::istream &in, label &&data);
  std::istream &operator>>(std::istream &in, LongLong &&data);
  std::istream &operator>>(std::istream &in, uLongLong &&data);
  std::istream &operator>>(std::istream &in, String &&data);
}
#endif
