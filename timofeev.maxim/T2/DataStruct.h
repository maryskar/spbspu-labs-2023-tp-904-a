#ifndef DATASTRUCT_H
#define DATASTRUCT_H
// [DBL SCI]	[CMP LSP]
#include <iostream>
#include <string>
#include <complex>
namespace timofeev
{
  using complex = std::complex< double >;
  struct DataStruct
  {
    double key1;
    complex key2;
    std::string key3;
  };
}
#endif
