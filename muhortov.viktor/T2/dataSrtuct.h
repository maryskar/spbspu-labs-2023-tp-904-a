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
  std::istream &operator>>(std::istream &input, dataStruct &dest);
  std::ostream &operator<<(std::ostream &output, const std::complex< double > &dest);
  std::ostream &operator<<(std::ostream &output, const std::pair< long long, unsigned long long > &dest);
  std::ostream &operator<<(std::ostream &output, const dataStruct &src);
}

#endif
