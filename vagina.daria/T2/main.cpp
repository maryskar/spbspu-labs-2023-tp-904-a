#include <vector>
#include <iterator>
#include "DataStruct.h"

//(:key2 0b1101 : key3 "was" : key1 5.45e-02 :)

int main()
{
  std::vector<DataStruct> data;

  std::copy(std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
  );

  std::cout << "Data:\n";
  std::copy(std::begin(data),
            std::end(data),
            std::ostream_iterator<DataStruct>(std::cout, "\n")
  );
  return 0;
}
