#include "data_struct.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>
#include <deque>
#include <sstream>

int main()
{
  const std::streamsize max_stream_size = std::numeric_limits< std::streamsize >::max();
  using in_data_iter = std::istream_iterator< shestakov::DataStruct >;
  using out_data_iter = std::ostream_iterator< shestakov::DataStruct >;
  std::deque< shestakov::DataStruct > data;
  std::istringstream iss { "(:key1 'a':key2 #c(0.5 -0.5):key3 \"Data\":)" };
  while (!iss.eof())
  {
    std::copy(in_data_iter(iss), in_data_iter(), std::back_inserter(data));
    if (!iss)
    {
      iss.clear();
      iss.ignore(max_stream_size, '\n');
    }
  }
  std::sort(data.begin(), data.end(), shestakov::compareValues);
  std::copy(std::begin(data), std::end(data), out_data_iter(std::cout, "\n"));
  return 0;
}
