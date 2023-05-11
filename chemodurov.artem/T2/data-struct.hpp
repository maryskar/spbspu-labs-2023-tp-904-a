#ifndef T2_DATA_STRUCT_HPP
#define T2_DATA_STRUCT_HPP
#include <string>

namespace chemodurov
{
  struct DataStrct
  {
    double key1;
    long long key2;
    std::string key3;
  };

  std::istream & operator>>(std::istream & in, DataStrct & data);
  std::ostream & operator<<(std::ostream & out, const DataStrct & data);
}

#endif
