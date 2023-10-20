#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>
#include <deque>
#include "datastruct.h"
#include <sstream>
using namespace kozyrin;

int main() {
  using ist_iter = std::istream_iterator< DataStruct >;
  using ost_iter = std::ostream_iterator< DataStruct >;
  std::deque< DataStruct > data;
  std::stringstream yes("(:key2 10ull:key1 5.45e-2:key3 \"Data\":)");
  //while (!std::cin.eof())
  //{
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(ist_iter(yes), ist_iter(), std::back_inserter(data));
  //}
  std::sort(data.begin(), data.end(), comp);
  std::copy(std::begin(data), std::end(data), ost_iter(std::cout, "\n"));
  std::cout << data.size();
}
