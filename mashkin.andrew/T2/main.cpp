#include <iostream>
#include <vector>
#include "dataStruct.h"

int main()
{
  std::vector< mashkin::DataStruct > res;
  std::vector< mashkin::DataStruct >::iterator iter;
  iter = res.begin();
  while (std::cin)
  {
    mashkin::DataStruct data;
    std::cin >> data;
    res.insert(iter, data);
    ++iter;
  }
  return 0;
}
