#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <string>
#include "data.h"

int main()
{
  std::list< chulkov::Data > resl;
  chulkov::Comparator comp;
  using istIter = std::istream_iterator< chulkov::Data >;
  while (!std::cin.eof()) {
    std::copy(istIter(std::cin), istIter(), std::back_inserter(resl));
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  using ostIter = std::ostream_iterator< chulkov::Data >;
  resl.sort(comp);
  std::copy(std::begin(resl), std::end(resl), ostIter(std::cout, "\n"));
  return 0;
}
