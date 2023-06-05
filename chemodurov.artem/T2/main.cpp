#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "data-struct.hpp"

int main()
{
  constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
  std::vector< chemodurov::DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(max_size, '\n');
    }
    using istr_it_data_t = std::istream_iterator< chemodurov::DataStruct >;
    std::copy(istr_it_data_t(std::cin), istr_it_data_t(), std::back_inserter(data));
  }

  std::sort(data.begin(), data.end(), chemodurov::isLess);

  std::copy(data.begin(), data.end(), std::ostream_iterator< chemodurov::DataStruct >(std::cout, "\n"));
  return 0;
}
