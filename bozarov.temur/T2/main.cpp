#include <iostream>
#include <deque>
#include <iterator>
#include <algorithm>
#include <limits>
#include "DataStruct.hpp"
#include "TypesIO.hpp"

int main()
{
  std::deque< bozarov::DataStruct > data;
  while (!std::cin.eof()) {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    using i_iter = std::istream_iterator< bozarov::DataStruct >;
    std::copy(i_iter(std::cin), i_iter(), std::back_inserter(data));
  }
  std::sort(std::begin(data), std::end(data), bozarov::compare);
  using o_iter = std::ostream_iterator< bozarov::DataStruct >;
  std::copy(std::begin(data), std::end(data), o_iter(std::cout, "\n"));
  return 0;
}
