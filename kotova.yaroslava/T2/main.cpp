#include <deque>
#include <iterator>
#include <algorithm>
#include <limits>
#include "data_struct.hpp"

int main()
{
  using ist_iter = std::istream_iterator< kotova::DataStruct >;
  using ost_iter = std::ostream_iterator< kotova::DataStruct >;
  std::deque< kotova::DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(ist_iter(std::cin), ist_iter(), std::back_inserter(data));
  }
  std::sort(data.begin(), data.end(), kotova::check);
  std::copy(std::begin(data), std::end(data), ost_iter(std::cout, "\n"));
  return 0;
}
