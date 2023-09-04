#include <iostream>
#include <vector>
#include <iterator>
#include "data_struct.h"

int main()
{
  std::vector< structure::DataStruct > data;
  using i_iter = std::istream_iterator< structure::DataStruct >;
  using o_iter = std::ostream_iterator< structure::DataStruct >;
  while (!std::cin.eof())
  {
    std::copy(i_iter(std::cin), i_iter(), std::back_inserter(data));
    if (std::cin.rdstate() == std::ios::failbit)
    {
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cin.clear();
    }
  }
}
