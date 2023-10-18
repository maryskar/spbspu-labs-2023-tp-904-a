#ifndef DATASRTUCT_HPP
#define DATASRTUCT_HPP
#include <complex>
#include <string>

namespace muhortov {
  struct DataStruct {
    std::complex< double > key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  struct comparator {
    bool operator()(const DataStruct &lhs, const DataStruct &rhs) const;
  };
}

#endif
