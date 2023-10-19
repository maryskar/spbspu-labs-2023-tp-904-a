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

  bool compare(const dataStruct &lhs, const dataStruct &rhs);
}

#endif
