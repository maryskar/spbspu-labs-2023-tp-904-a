#include <vector>
#include <iterator>
#include <algorithm>
#include "DataStruct.h"

//(:key2 0b1101 : key3 "was" : key1 5.45e-02 :)
//(:key1 7.45e-02 : key2 0b1001 : key3 "something" :)
//(:key1 7.45e-02 : key2 0b1001 : key3 "some" :)
//(:key1 3.45e-02 : key2 0b1321 : key3 "so" :)
//(:key2 0b1101 : key3 "was good" : key1 8.72e-02 :)
//(:key1 2.45e-02 : key2 0b11011 : key3 "deadline" :)
//(:key2 0B1111 : key3 "Data" : key1 5.45e-02 :)
//(:key3 "Datad" : key1 9.45e-00 : key2 0B11321 :)
//(:key1 "Data" : key2(:N - 3 : D 2 : ) : key3 "Dataa" : )
//(:key1 0.0d : key2(:N - 3 : D 2 : ) : key3 "Datab" : )
//(:key1 #c(0.5 - 0.5) : key2(:N - 3 : D 2 : ) : key3 "Datad" : )
//(:key1 'a' : key2(:N - 3 : D 2 : ) : key3 "Datae" : )
//(:key1 00 : key2 0b1111 : key3 "Dataf" : )
//(:key1 1.5e-1 : key2 0b10101 : key3 "Datac" : )

int main()
{
  std::vector<DataStruct> data;
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::copy(
            std::istream_iterator< DataStruct >(std::cin),
            std::istream_iterator< DataStruct >(),
            std::back_inserter(data)
    );
  }
  std::sort(data.begin(), data.end(), comp);
  std::cout << "Data:\n";
  std::copy(std::begin(data),
            std::end(data),
            std::ostream_iterator< DataStruct >(std::cout, "\n")
  );
  return 0;
}
