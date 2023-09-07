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
  std::ifstream &operator>>(std::ifstream &in, delimiter &&data);
  std::ifstream &operator>>(std::ifstream &in, label &&data);
  std::ifstream &operator>>(std::ifstream &in, LongLong &&data);
  std::ifstream &operator>>(std::ifstream &in, uLongLong &&data);
  std::ifstream &operator>>(std::ifstream &in, String &&data);
}
#endif
