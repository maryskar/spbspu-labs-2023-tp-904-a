#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "datastruct.hpp"
#include "typesio.hpp"

int main()
{
  std::vector< gulyaev::DataStruct > data;
  while (!std::cin.eof()) {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    using i_iter = std::istream_iterator< gulyaev::DataStruct >;
    std::copy(i_iter(std::cin), i_iter(), std::back_inserter(data));
  }
  std::sort(std::begin(data), std::end(data), gulyaev::isLess);
  std::copy(std::begin(data), std::end(data),
    std::ostream_iterator< gulyaev::DataStruct >(std::cout, "\n"));
  return 0;
}
