#ifndef KONCHEV_MAKSIM_IOTYPES_H
#define KONCHEV_MAKSIM_IOTYPES_H
#include <string>
#include <fstream>
#include "DataStruct.h"
namespace konchev
{
  struct DelimiterIO
  {
    char exp;
  };
  struct LabelIO
  {
    std::string str;
  };
  struct LongLongIO
  {
    long long &ref;
  };
  struct uLongLongIO
  {
    unsigned long long &ref;
  };
  struct StringIO
  {
    std::string &ref;
  };
  std::istream &operator>>(std::istream &in, DelimiterIO &&data);
  std::istream &operator>>(std::istream &in, LabelIO &&data);
  std::istream &operator>>(std::istream &in, LongLongIO &&data);
  std::istream &operator>>(std::istream &in, uLongLongIO &&data);
  std::istream &operator>>(std::istream &in, StringIO &&data);
}
#endif
