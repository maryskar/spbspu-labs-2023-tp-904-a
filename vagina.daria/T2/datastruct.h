#ifndef T2_DATASTRUCT_H
#define T2_DATASTRUCT_H

#include <string>
#include <iostream>
#include <bitset>

struct DataStruct
{
  double key1;
  unsigned long long key2;
  std::string key3;
};
struct DoubleIO
{
  double &num;
};
struct BinUnsignedLongLongIO
{
  unsigned long long &num;
};
struct StringIO
{
  std::string &string;
};
struct LiteralIO
{
  std::string literal;
};
struct DelimiterIO
{
  char char_;
};
std::istream &operator>>(std::istream &in, DoubleIO &&dest);
std::istream &operator>>(std::istream &in, BinUnsignedLongLongIO &&dest);
std::istream &operator>>(std::istream &in, StringIO &&dest);
std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
std::istream &operator>>(std::istream &in, DataStruct &dest);
std::istream &operator>>(std::istream& in, LiteralIO&& dest);
std::ostream &operator<<(std::ostream &out, const DataStruct &dest);

#endif //T2_DATASTRUCT_H
