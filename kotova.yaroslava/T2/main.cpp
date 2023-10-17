#include <vector>
#include <limits>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "data_struct.hpp"

int main()
{
  std::vector< kotova::DataStruct > data;
  while (!std::cin.eof())
  {
    std::cin.clear();
    using iter_d = std::istream_iterator< kotova::DataStruct >;
    std::copy(iter_d(std::cin),iter_d(), std::back_inserter(data));
  }
  std::sort(data.begin(), data.end(), kotova::check);
  std::copy(data.begin(), data.end(), std::ostream_iterator< kotova::DataStruct >(std::cout, "\n"));
}
