#include <fstream>
#include <iostream>
#include <iterator>
#include "Polygon.hpp"
#include "getArea.hpp"

int main()
{
  std::ifstream in ("input.txt");
  using inIter = std::istream_iterator< malaya::Polygon >;
  std::vector< malaya::Polygon > data;
  std::copy(inIter(in), inIter(), std::back_inserter(data));

  return 0;
}
