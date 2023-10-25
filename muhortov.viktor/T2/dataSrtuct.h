#ifndef DATASRTUCT_HPP
#define DATASRTUCT_HPP
#include <complex>
#include <string>

namespace muhortov{
  struct DataStruct {
    std::complex< double > key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  bool compare(const DataStruct &lhs, const DataStruct &rhs);
  std::istream &operator>>(std::istream &input, DataStruct &dest);
  std::ostream &operator<<(std::ostream &output, const std::complex< double > &dest);
  std::ostream &operator<<(std::ostream &output, const std::pair< long long, unsigned long long > &dest);
  std::ostream &operator<<(std::ostream &output, const DataStruct &src);
}

#endif
