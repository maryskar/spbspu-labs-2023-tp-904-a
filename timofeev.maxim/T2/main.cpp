#include <iostream>
#include <iterator>
#include <vector>
#include "comparator.h"
#include "DataStruct.h"
int main()
{

  std::vector< Data > data;
  std::copy( std::istream_iterator< Data >(iss), std::istream_iterator< Data >(), std::back_inserter(data));

  std::copy( std::begin(data), std::end(data), std::ostream_iterator< Data >(std::cout, "\n") );

  return 0;
}