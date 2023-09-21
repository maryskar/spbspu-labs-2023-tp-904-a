#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>
#include <deque>
#include "data_struct.h"

int main()
{
  const std::streamsize max_stream_size = std::numeric_limits< std::streamsize >::max();
  using in_data_iter = std::istream_iterator< shestakov::DataStruct >;
  using out_data_iter = std::ostream_iterator< shestakov::DataStruct >;
  std::deque< shestakov::DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(in_data_iter(std::cin), in_data_iter(), std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(max_stream_size, '\n');
    }
  }
  std::sort(data.begin(), data.end(), shestakov::compareValues);
  std::copy(std::begin(data), std::end(data), out_data_iter(std::cout, "\n"));
  return 0;
}
