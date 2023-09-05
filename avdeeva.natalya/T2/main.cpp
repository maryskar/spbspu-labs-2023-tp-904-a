#include <deque>
#include <iostream>
#include <iterator>
#include <limits>
#include <algorithm>
#include "datastruct.h"

int main()
{
  std::deque< avdeeva::DataStruct > data;
  avdeeva::Comparator comparator;
  using inIter = std::istream_iterator< avdeeva::DataStruct >;
  using outIter = std::ostream_iterator< avdeeva::DataStruct >;
  while (!std::cin.eof())
  {
    std::copy(inIter(std::cin), inIter(), std::back_inserter(data));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), comparator);
  std::copy(std::begin(data), std::end(data), outIter(std::cout, "\n"));
  return 0;
}
