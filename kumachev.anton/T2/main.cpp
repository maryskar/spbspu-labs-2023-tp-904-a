#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <iterator>
#include "data_struct.h"
#include "sort.h"

int main()
{
  std::vector< T2::DataStruct > data;
  auto backInserter = std::back_inserter(data);
  std::istream &in = std::cin;

  while (!in.eof()) {
    T2::DataStruct dataStruct;
    in >> dataStruct;

    if (!in.fail()) {
      *backInserter = dataStruct;
      ++backInserter;
    }
    else {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end(), T2::compareData);
  std::copy(data.begin(), data.end(), std::ostream_iterator< T2::DataStruct >(std::cout));
  return 0;
}
