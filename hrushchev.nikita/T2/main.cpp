#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "datastruct.hpp"

int main()
{
  constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
  std::vector< hrushchev::DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(max_size, '\n');
    }
    using data_istr_iter = std::istream_iterator< hrushchev::DataStruct >;
    std::copy(data_istr_iter(std::cin), data_istr_iter(), std::back_inserter(data));
  }

  std::sort(data.begin(), data.end(), hrushchev::Comparator());

  std::copy(data.begin(), data.end(), std::ostream_iterator< hrushchev::DataStruct >(std::cout, "\n"));
  return 0;
}