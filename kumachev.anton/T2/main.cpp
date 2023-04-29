#include <vector>
#include <iostream>
#include <limits>
#include <fstream>
#include "data_struct.h"

int main()
{
  std::vector< T2::DataStruct > data;
  auto backInserter = std::back_inserter(data);
  std::ifstream in("input.txt");

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

  std::cout << data.size() << '\n';
  return 0;
}
