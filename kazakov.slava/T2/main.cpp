#include<deque>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <limits>
#include "DataStructur.h"

int main()
{
  std::deque< kazakov::DataStructur > v;
  while (!std::cin.eof())
  {
    auto cin = std::istream_iterator< kazakov::DataStructur >(std::cin);
    auto iterator = std::istream_iterator< kazakov::DataStructur >();
    auto inserter = std::inserter(v, v.end());
    std::copy(cin, iterator, inserter);
    if (std::cin.fail())
    {
      std::cin.clear();
      auto maxstream = std::numeric_limits< std::streamsize >::max();
      std::cin.ignore(maxstream, ')');
    }
  }
  std::sort(v.begin(), v.end(), kazakov::comparator);
  auto cout = std::ostream_iterator< kazakov::DataStructur >(std::cout, "\n");
  std::copy(v.begin(), v.end(), cout);
  return 0;
}
