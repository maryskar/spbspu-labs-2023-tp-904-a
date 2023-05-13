#include <fstream>
#include <iostream>
#include <iterator>
#include "Polygon.hpp"
#include "getArea.hpp"

int main()
{
  std::ifstream in ("input.txt");
  std::vector< malaya::Polygon > data;
  std::copy(std::istream_iterator< malaya::Polygon >(in),
    std::istream_iterator< malaya::Polygon >(),
        std::back_inserter(data));

  return 0;
}
