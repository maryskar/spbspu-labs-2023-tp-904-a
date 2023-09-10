#include <vector>
#include <limits>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "data_struct.hpp"

int main()
{
  using in_iter = std::istream_iterator< kotova::DataStruct >;
  using out_iter = std::ostream_iterator< kotova::DataStruct >;
  std::vector< kotova::DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(in_iter(std::cin), in_iter(), std::back_inserter(data));
  }
  std::sort(data.begin(), data.end(), kotova::check);
  std::copy(std::begin(data), std::end(data), out_iter(std::cout, "\n"));

}
