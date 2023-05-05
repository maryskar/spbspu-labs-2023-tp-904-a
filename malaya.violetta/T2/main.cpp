#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include "DataStruct.hpp"
int main()
{
  //std::ifstream in("input.txt");
  std::vector< malaya::DataStruct > data;
  std::copy(std::istream_iterator< malaya::DataStruct >(std::cin), std::istream_iterator< malaya::DataStruct >(),
            std::back_inserter(data));
  std::sort(data.begin(), data.end(), malaya::DataComparator{});
  std::copy(std::begin(data), std::end(data),
            std::ostream_iterator< malaya::DataStruct >(std::cout, "\n"));
  return 0;
}
