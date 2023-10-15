#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>
#include <deque>
#include "DataStruct.h"

int main()
{
  const std::streamsize max_stream_size = std::numeric_limits< std::streamsize >::max();
  using out_data_iter = std::ostream_iterator< konchev::DataStruct >;
  using in_data_iter = std::istream_iterator< konchev::DataStruct >;
  std::deque< konchev::DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(in_data_iter (std::cin), in_data_iter(), std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(max_stream_size, '\n');
    }
  }
  std::sort(data.begin(), data.end(), konchev::compareData);
  std::copy(std::begin(data), std::end(data), out_data_iter(std::cout, "\n"));
  return 0;
}
