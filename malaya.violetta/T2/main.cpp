#include <deque>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>
#include "DataStruct.hpp"
int main()
{
  std::deque< malaya::DataStruct > data;
  using inIter = std::istream_iterator< malaya::DataStruct >;
  using outIter = std::ostream_iterator< malaya::DataStruct >;
  while (!std::cin.eof())
  {
    std::copy(inIter(std::cin), inIter(), std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), malaya::DataComparator{});
  std::copy(std::begin(data), std::end(data), outIter(std::cout, "\n"));
  return 0;
}
