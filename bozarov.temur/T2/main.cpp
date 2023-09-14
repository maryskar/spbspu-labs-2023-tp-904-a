#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "DataStruct.hpp"
#include "TypesIO.hpp"

int main()
{
  std::vector< bozarov::DataStruct > data;
  while (!std::cin.eof()) {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    using i_iter = std::istream_iterator< bozarov::DataStruct >;
    std::copy(i_iter(std::cin), i_iter(), std::back_inserter(data));
  }
  std::sort(std::begin(data), std::end(data), bozarov::compare);
  std::copy(std::begin(data), std::end(data),
      std::ostream_iterator< bozarov::DataStruct >(std::cout, "\n"));
  return 0;
}
