#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data_struct.h"

int main()
{
  std::vector< skarlygina::DataStruct > data;
  using i_iter = std::istream_iterator< skarlygina::DataStruct >;
  using o_iter = std::ostream_iterator< skarlygina::DataStruct >;
  while (!std::cin.eof())
  {
    std::copy(i_iter(std::cin), i_iter(), std::back_inserter(data));
    if (std::cin.rdstate() == std::ios::failbit)
    {
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cin.clear();
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(data.begin(), data.end(), o_iter(std::cout, "\n"));
}
