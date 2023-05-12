#include <iostream>
#include <vector>
#include <iterator>
#include "data-struct.hpp"

int main()
{
  std::vector< chemodurov::DataStrct > data;
  std::copy(
    std::istream_iterator< chemodurov::DataStrct >(std::cin),
    std::istream_iterator< chemodurov::DataStrct >(),
    std::back_inserter(data)
  );
  std::copy(data.begin(), data.end(), std::ostream_iterator< chemodurov::DataStrct >(std::cout, "\n"));
  return 0;
}
