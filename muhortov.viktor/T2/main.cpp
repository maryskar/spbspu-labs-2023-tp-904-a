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
  auto iteratorOutput = iteratorInput();
  const std::streamsize maxStreamSize = std::numeric_limits< std::streamsize >::max();
  std::deque< dataStruct > data;
  while (!std::cin.eof()) {
    std::copy(iteratorInput(std::cin), iteratorOutput, std::back_inserter(data));
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(maxStreamSize, '\n');
    }
  }

  std::sort(data.begin(), data.end(), comparator);
  std::copy(data.begin(), data.end(). std::ostream_iterator< dataStruct>(std::cout, "\n"));
  return 0;
}
