#ifndef KONCHEV_MAKSIM_DATASTRUCT_H
#define KONCHEV_MAKSIM_DATASTRUCT_H
#include <string>
#include <fstream>
namespace konchev
{
  struct DataStruct
  {
    long long key1;
    unsigned long long key2;
    std::string key3;
  };
  bool compareData(const DataStruct &lhs, const DataStruct &rhs);
  std::istream &operator>>(std::istream &in, DataStruct &data);
  std::ostream &operator<<(std::ostream &out, const DataStruct &data);
};
#endif
