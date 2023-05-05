#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>
#include "DataStruct.hpp"
int main()
{
  std::vector< malaya::DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(std::istream_iterator< malaya::DataStruct >(std::cin), std::istream_iterator< malaya::DataStruct >(),
              std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), malaya::DataComparator{});
  std::copy(std::begin(data), std::end(data),
            std::ostream_iterator< malaya::DataStruct >(std::cout, "\n"));
  return 0;
}
