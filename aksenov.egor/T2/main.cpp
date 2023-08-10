#include <iostream>
#include <vector>
#include <iterator>
#include "DataStruct.h"
int main()
{
  std::vector< aksenov::DataStruct > data;
  using inputIter = std::istream_iterator< aksenov::DataStruct >;
  using outputIter = std::ostream_iterator< aksenov::DataStruct >;
  std::cout << "Init commit";
}
