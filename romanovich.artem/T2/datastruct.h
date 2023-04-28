#ifndef ROMANOVICH_ARTEM_DATASTRUCT_H
#define ROMANOVICH_ARTEM_DATASTRUCT_H
#include <string>
#include <utility>
using return_tuple = std::tuple< unsigned long long, std::pair< long long, unsigned long long >, std::string >;
struct DataStruct
{
  explicit DataStruct(return_tuple tuple);
  void printDS() const;
  static bool compareK1(const DataStruct &a, const DataStruct &b)
  {
    return a.key1 < b.key1;
  }
  static bool compareK2(const DataStruct &a, const DataStruct &b)
  {
    return (a.key2.first / a.key2.second) < (b.key2.first / b.key2.second);
  }
  static bool compareK3(const DataStruct &a, const DataStruct &b)
  {
    return a.key3.length() < b.key3.length();
  }
  static void print(const DataStruct &dataStruct)
  {
    dataStruct.printDS();
  }
  unsigned long long key1;
  std::pair< long long, unsigned long long > key2;
  std::string key3;
};
#endif
