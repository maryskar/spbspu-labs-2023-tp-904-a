#include <iostream>
#include <deque>
#include <limits>
#include <iterator>
#include <algorithm>
#include "dataStruct.h"

int main()
{
  std::deque< samoilenko::DataStruct > data;
  using iter_of_inp = std::istream_iterator< samoilenko::DataStruct >;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(iter_of_inp(std::cin), iter_of_inp(), std::back_inserter(data));
  }
  using iter_of_out = std::ostream_iterator< samoilenko::DataStruct >;
  std::sort(data.begin(), data.end(), samoilenko::compareData);
  std::copy(data.begin(), data.end(), iter_of_out(std::cout, "\n"));
  return 0;
}
