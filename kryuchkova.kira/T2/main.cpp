#include <iostream>
#include <deque>
#include <iterator>
#include <algorithm>
#include <limits>
#include "data_struct.h"

int main()
{
  std::deque< kryuchkova::DataStruct > data;
  using input_iter = std::istream_iterator< kryuchkova::DataStruct >;
  using output_iter = std::ostream_iterator< kryuchkova::DataStruct >;
  while (!std::cin.eof())
  {
    std::copy(input_iter(std::cin), input_iter(), std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), kryuchkova::CmpData);
  std::copy(data.begin(), data.end(), output_iter(std::cout, "\n"));
  return 0;
}
