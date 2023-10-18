#ifndef DATASRTUCT_HPP
#define DATASRTUCT_HPP
#include <complex>
#include <string>

namespace muhortov {
  struct dataStruct {
    std::complex< double > key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  struct comparator {
    bool operator()(const dataStruct &lhs, const dataStruct &rhs) const;
  };
}

#endif
