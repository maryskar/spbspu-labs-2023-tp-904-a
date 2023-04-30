#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "DataStruct.h"

int main() {
  std::vector< DataStruct::DataStruct > data;

  std::copy(std::istream_iterator< DataStruct::DataStruct >(std::cin),
            std::istream_iterator< DataStruct::DataStruct >(),
            std::back_inserter(data));

  std::sort(data.begin(), data.end(), DataStruct::Comp);

  std::copy(std::begin(data), std::end(data),
            std::ostream_iterator< DataStruct::DataStruct >(std::cout, "\n"));

  return 0;
}
