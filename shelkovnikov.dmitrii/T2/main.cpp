#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "data_structs.h"
int main()
{
  using data_struct = dimkashelk::DataStruct;
  using in_it_begin = std::istream_iterator< data_struct >(std::cin);
  dimkashelk::Comparator comparator;
  std::vector< data_struct > data;
  std::copy(
    std::istream_iterator< data_struct >(std::cin),
    std::istream_iterator< data_struct >(),
    std::back_inserter(data)
  );
  std::sort(data.begin(), data.end(), comparator);
  std::copy(std::begin(data), std::end(data),
    std::ostream_iterator< data_struct >(std::cout, "\n")
  );
  return 0;
}
