#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <iterator>
#include "data_struct.h"
#include "io.h"

int main()
{
  std::vector< kumachev::DataStruct > data;
  auto backInserter = std::back_inserter(data);
  std::istream &in = std::cin;

  while (!in.eof()) {
    kumachev::DataStruct dataStruct;
    in >> dataStruct;

    if (!in.fail()) {
      *backInserter = dataStruct;
      ++backInserter;
    } else {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end(), kumachev::DataStructComparator{});
  std::copy(
    data.begin(),
    data.end(),
    std::ostream_iterator< kumachev::DataStruct >(std::cout, "\n")
  );

  return 0;
}
