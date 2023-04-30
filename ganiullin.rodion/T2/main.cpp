#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "DataStruct.h"

int main() {
  std::vector<ganiullin::DataStruct> data;
  ganiullin::Comparator Comp;

  std::copy(std::istream_iterator<ganiullin::DataStruct>(std::cin),
            std::istream_iterator<ganiullin::DataStruct>(),
            std::back_inserter(data));

  std::sort(data.begin(), data.end(), Comp);

  std::copy(std::begin(data), std::end(data),
            std::ostream_iterator<ganiullin::DataStruct>(std::cout, "\n"));

  return 0;
}
