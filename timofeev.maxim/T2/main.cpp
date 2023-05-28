#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
int main()
{
  using nspace::Data;

  std::vector< Data > data;
  std::istringstream iss("{ \"key1\": 1.0d, \"key2\": \"Let madness release you\" }");

  std::copy(
      std::istream_iterator< Data >(iss),
      std::istream_iterator< Data >(),
      std::back_inserter(data)
  );

  std::cout << "Data:\n";
  std::copy(
      std::begin(data),
      std::end(data),
      std::ostream_iterator< Data >(std::cout, "\n")
  );

  return 0;
}