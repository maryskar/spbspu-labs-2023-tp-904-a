#include <vector>
#include <iostream>
#include <iterator>
#include <fstream>
#include "data_struct.h"

int main()
{
  std::vector< T2::DataStruct > data;
  std::ifstream in("input.txt");

  std::copy(std::istream_iterator< T2::DataStruct >(in),
            std::istream_iterator< T2::DataStruct >{},
            std::back_inserter(data)
  );

  std::cout << data.size() << '\n';
  return 0;
}
