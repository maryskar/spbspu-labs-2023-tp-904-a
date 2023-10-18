#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <deque>
#include "dataSrtuct.h"
#include "io.h"

using namespace muhortov;

int main() {
  using iteratorInput = std::istream_iterator< dataStruct >;
  const std::streamsize maxStreamSize = std::numeric_limits< std::streamsize >::max();
  std::deque< dataStruct > data;
  std::cout << "help\n";
  while (!std::cin.eof()) {
    std::copy(iteratorInput(std::cin), iteratorInput(), std::back_inserter(data));
    std::cout << "help\n";
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(maxStreamSize, '\n');
    }
  }

  std::sort(data.begin(), data.end(), comparator());
  std::copy(std::begin(data), std::end(data), std::ostream_iterator< dataStruct >(std::cout, "\n"));
  return 0;
}
