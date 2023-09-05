#include <iterator>
#include <algorithm>
#include <limits>
#include <list>
#include "DataStruct.h"

int main()
{
  using ds_t = mishanina::DataStruct;
  using ist_iter = std::istream_iterator< ds_t >;
  using ost_iter = std::ostream_iterator< ds_t >;
  std::list< ds_t > data;
  mishanina::Comparator comp;
  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(ist_iter(std::cin), ist_iter(), std::back_inserter(data));
  }
  data.sort(comp);
  std::copy(std::begin(data), std::end(data), ost_iter(std::cout, "\n"));
  return 0;
}
