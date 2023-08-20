#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>
#include <deque>
#include "data_struct.hpp"

int main()
{
  const std::streamsize max_stream_size = std::numeric_limits< std::streamsize >::max();
  using data_t = zhuravlev::DataStruct;
  using in_data_iter = std::istream_iterator< data_t >;
  using out_data_iter = std::ostream_iterator< data_t >;
  std::deque< data_t > data;
  do
  {
    if(std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(max_stream_size, '\n');
    }
   std::copy(in_data_iter(std::cin), in_data_iter (), std::back_inserter(data));
  }
  while(!std::cin.eof());
  return 0;
}
