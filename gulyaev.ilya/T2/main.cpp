#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "datastruct.hpp"
#include "typesio.hpp"

int main()
{
  std::vector< gulyaev::DataStruct > data;
  while (!std::cin.eof()) {
    std::cin.clear();
    using i_iter = std::istream_iterator< gulyaev::DataStruct >;
    std::copy(i_iter(std::cin), i_iter(), std::back_inserter(data));
  }
  std::cout << "Data:\n";
  std::sort(std::begin(data), std::end(data), gulyaev::isLess);
  std::copy(std::begin(data), std::end(data),
    std::ostream_iterator< gulyaev::DataStruct >(std::cout, "\n"));
  return 0;
}
