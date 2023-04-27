#ifndef ROMANOVICH_ARTEM_DATASTRUCT_H
#define ROMANOVICH_ARTEM_DATASTRUCT_H
#include <string>
#include <utility>
struct DataStruct
{
  DataStruct(unsigned long long int key1, std::pair<long long int, unsigned long long int> key2, std::string key3);
  DataStruct(
    std::tuple<unsigned long long int, std::pair<long long int, unsigned long long int>, std::basic_string<char>> tuple1);
  unsigned long long key1;
  void print() const;
private:
  std::pair<long long, unsigned long long> key2;
  std::string key3;
};
#endif
