#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "iofmtguard.hpp"
#include "data_struct.hpp"

int main()
{
  using zhuravlev::DataStruct;
  using iter_data = std::istream_iterator< zhuravlev::DataStruct >;
  using output_data_iter = std::ostream_iterator<zhuravlev::DataStruct >;
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
    }
    std::copy(std::istream_iterator< DataStruct >(std::cin), iter_data(),std::back_inserter(data));
  }
  std::sort(data.begin(), data.end(), zhuravlev::dataComparator);
  std::copy(data.begin(), data.end(), output_data_iter(std::cout, "\n"));
  return 0;
}
