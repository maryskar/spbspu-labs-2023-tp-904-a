#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "datastruct.hpp"
#include "typesio.hpp"

int main()
{
  using namespace gulyaev;
  std::vector< DataStruct > data;
  while (!std::cin.eof()) {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(std::istream_iterator< DataStruct >(std::cin),
        std::istream_iterator< DataStruct >(),
        std::back_inserter(data)
    );
  }
  std::sort(std::begin(data), std::end(data), gulyaev::isLess);
  std::copy(std::begin(data),
      std::end(data),
      std::ostream_iterator< DataStruct >(std::cout, "\n")
  );
  return 0;
}
