#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data-struct.hpp"

int main()
{
  std::vector< chemodurov::DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::string line;
      std::getline(std::cin, line);
    }
    using istr_it_data_t = std::istream_iterator< chemodurov::DataStruct >;
    std::copy(istr_it_data_t(std::cin), istr_it_data_t(), std::back_inserter(data));
  }

  std::sort(data.begin(), data.end(), chemodurov::isLess);

  std::copy(data.begin(), data.end(), std::ostream_iterator< chemodurov::DataStruct >(std::cout, "\n"));
  return 0;
}
