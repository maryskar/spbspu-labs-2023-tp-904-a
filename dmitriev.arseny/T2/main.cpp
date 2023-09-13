#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>



int main()
{
  using data_t = int;
  std::vector< data_t > vec;

  std::copy(std::istream_iterator< data_t >(std::cin), std::istream_iterator< data_t >(), std::back_inserter(vec));
  std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator< data_t >(std::cout, "_"));

  return 0;
}
