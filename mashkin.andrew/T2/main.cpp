#include <iostream>
#include <vector>
#include <string>
#include "dataStruct.h"

int main()
{
  std::vector< mashkin::DataStruct > res;
  std::vector< mashkin::DataStruct >::iterator iter;
  iter = res.begin();
  while (!std::cin.eof())
  {
    mashkin::DataStruct data;
    std::cin >> data;
    if (std::cin.fail())
    {
      std::string line;
      std::cin.clear();
      std::getline(std::cin, line);
    }
    std::cout << data.key1 << " " << data.key2 << " " << data.key3 << "\n";
    //res.insert(iter, data);
    //++iter;
  }
  return 0;
}
