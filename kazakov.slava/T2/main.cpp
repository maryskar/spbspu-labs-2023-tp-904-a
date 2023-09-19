#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <limits>
#include"DataStructur.h"

int main()
{
  std::vector< kazakov::DataStructur > v;
  while (true)
  {
    std::copy(std::istream_iterator< kazakov::DataStructur >(std::cin),
        std::istream_iterator< kazakov::DataStructur >(),
        std::inserter(v, v.end())
    );
    if (std::cin.eof())
    {
      break;
    }
    if (std::cin.fail())
    {
      std::cin.clear();
      auto maxstream = std::numeric_limits< std::streamsize >::max();
      std::cin.ignore(maxstream, ')');
    }
  }
  std::sort(v.begin(), v.end(), kazakov::comparator);
  std::copy(v.begin(), v.end(), std::ostream_iterator< kazakov::DataStructur >(std::cout, "\n"));
  return 0;
}
