#include <iostream>
#include <deque>
#include <limits>
#include <iterator>
#include <algorithm>
#include "dataStruct.h"

int main()
{
  using iter_of_inp = std::istream_iterator< samoilenko::DataStruct >;
  std::deque< samoilenko::DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(iter_of_inp(std::cin), iter_of_inp(), std::back_inserter(data));
  }
  std::sort(data.begin(), data.end(), samoilenko::compareData);
  std::copy(data.begin(), data.end(), std::ostream_iterator< samoilenko::DataStruct >(std::cout, "\n"));
  return 0;
}