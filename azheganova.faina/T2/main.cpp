#include <vector>
#include <iterator>
#include <algorithm>
#include "datastruct.h"

int main()
{
  using ist_iter = std::istream_iterator< azheganova::DataStruct >;
  std::vector< azheganova::DataStruct > data;
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::copy(ist_iter(std::cin), ist_iter(), std::back_inserter(data));
  }
  std::sort(data.begin(), data.end(), azheganova::compareValues);
  std::copy(std::begin(data), std::end(data), std::ostream_iterator< azheganova::DataStruct >(std::cout, "\n")
  );
  return 0;
}

