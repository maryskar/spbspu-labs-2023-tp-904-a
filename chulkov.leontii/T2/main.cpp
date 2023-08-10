#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

#include "data.h"

int main() {
  std::vector< chulkov::Data > resl;
  chulkov::Comparator comp;
  using istIter = std::istream_iterator< chulkov::Data >;
  while (!std::cin.eof()) {
    std::copy_n(istIter(std::cin), 3, std::back_inserter(resl));
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  using ostIter = std::ostream_iterator< chulkov::Data >;
  std::sort(std::begin(resl), std::end(resl), comp);
  std::copy(std::begin(resl), std::end(resl), ostIter(std::cout, "\n"));
  return 0;
}
