#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "data_struct.h"
#include "comparator.h"
int main()
{
  using data_struct = dimkashelk::DataStruct;
  using it_begin = std::istream_iterator< data_struct >;
  auto it_end = std::istream_iterator< data_struct >();
  auto out_begin = std::ostream_iterator< data_struct >(std::cout, "\n");
  dimkashelk::Comparator comparator;
  std::vector< data_struct > data;
  while (!std::cin.eof())
  {
    std::copy(it_begin(std::cin), it_end, std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::string to_skip;
      std::getline(std::cin, to_skip);
    }
  }
  std::sort(data.begin(), data.end(), comparator);
  std::copy(std::begin(data), std::end(data), out_begin);
  return 0;
}
