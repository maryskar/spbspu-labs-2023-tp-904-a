#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include "data-struct.hpp"

int main()
{
  using turkin::DataStruct;

  std::vector< DataStruct > data;
  std::istringstream iss("{ \"key1\": 1.0d, \"key2\": \"Let madness release you\" }");

  std::copy(
    std::istream_iterator< DataStruct >(iss),
    std::istream_iterator< DataStruct >(),
    std::back_inserter(data)
  );

  std::cout << "Data:\n";
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );

  return 0;
}
