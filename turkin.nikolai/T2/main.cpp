#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>
#include <limits>

#include "data-struct.hpp"

int main()
{
  using turkin::DataStruct;
  using turkin::Comparator;
  using isit = std::istream_iterator< DataStruct >;
  using osit = std::ostream_iterator< DataStruct >;

  std::deque< DataStruct > data;

  while (!std::cin.eof())
  {
    std::copy(isit(std::cin), isit(), std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  Comparator cmp;
  std::sort(data.begin(), data.end(), cmp);
  std::copy(data.begin(), data.end(), osit(std::cout, "\n"));

  return 0;
}
