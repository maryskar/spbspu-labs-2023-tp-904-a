#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "data_structs.h"
int main()
{
  using data_struct = dimkashelk::DataStruct;
  auto it_begin = std::istream_iterator< data_struct >(std::cin);
  auto it_end = std::istream_iterator< data_struct >();
  auto out_begin = std::ostream_iterator< data_struct >(std::cout, "\n");
  dimkashelk::Comparator comparator;
  std::vector< data_struct > data;
  while (!std::cin.eof()) {
    dimkashelk::DataStruct dataStruct;
    std::cin >> dataStruct;
    if (!std::cin)
    {
      data.push_back(dataStruct);
    }
    else
    {
      std::cin.clear();
    }
  }
  std::sort(data.begin(), data.end(), comparator);
  std::copy(std::begin(data), std::end(data), out_begin);
  return 0;
}
