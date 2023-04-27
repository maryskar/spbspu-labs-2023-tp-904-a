#include<vector>
#include<iostream>
#include <iterator>
#include"DataStruct.hpp"
int main()
{
  std::vector< malaya::DataStruct > data;
  //std::copy(
  //  std::istream_iterator< malaya::DataStruct >(std::cin),
  //  std::istream_iterator< malaya::DataStruct >(),
  //  std::back_inserter(data)
  //);
  while(std::cin) //возможно другое условие
  {
    std::copy(
      std::istream_iterator< malaya::DataStruct >(std::cin),
      std::istream_iterator< malaya::DataStruct >(),
      std::back_inserter(data)
    );
  }
  //добавить сортировку
  //написать компаратор
  std::cout << "Data:\n";
  std::copy(
    std::begin(data),
    std::end(data), // проверить
    std::ostream_iterator< malaya::DataStruct >(std::cout, "\n")
  );

  return 0;
}
