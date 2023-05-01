#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <iterator>
#include "datastruct.h"
#include "input.h"
void safeReplace(std::string &line, constr &oldStr, constr &newStr)
{
  long unsigned int pos = static_cast<long unsigned int>(line.find(oldStr));
  while (pos != std::string::npos)
  {
    line = line.replace(pos, oldStr.length(), newStr);
    pos = static_cast<int>(line.find(oldStr));
  }
}
int main()
{
  std::vector< romanovich::DataStruct > ds;
  std::copy(
    std::istream_iterator< romanovich::DataStruct >(std::cin),
    std::istream_iterator< romanovich::DataStruct >(),
    std::back_inserter(ds)
  );
  std::sort(ds.begin(), ds.end(), romanovich::DataStruct::compareK3);
  std::sort(ds.begin(), ds.end(), romanovich::DataStruct::compareK2);
  std::sort(ds.begin(), ds.end(), romanovich::DataStruct::compareK1);
  std::for_each(ds.begin(), ds.end(), romanovich::DataStruct::print);
  return 0;
}
