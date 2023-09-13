#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "datastruct.h"

int main()
{
  using data_t = dmitriev::DataStruct;
  std::vector< data_t > vec;

  std::copy(std::istream_iterator< data_t >(std::cin), std::istream_iterator< data_t >(), std::back_inserter(vec));



  std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator< data_t >(std::cout, "\n"));

  return 0;
}
