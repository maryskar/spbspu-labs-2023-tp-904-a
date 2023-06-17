#include <iostream>
#include <limits>
#include <deque>
#include <iterator>
#include <algorithm>
#include "datastruct.hpp"

int main()
{
  std::deque< hrushchev::DataStruct > data;

  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    using iter = std::istream_iterator< hrushchev::DataStruct >;
    std::copy(iter(std::cin), iter(), std::back_inserter(data));
  }

  std::sort(data.begin(), data.end(), hrushchev::Comparator());

  std::copy(data.begin(), data.end(), std::ostream_iterator< hrushchev::DataStruct >(std::cout, "\n"));
}
