#ifndef SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#define SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

namespace skalisusov
{
  struct Data: public std::__1::error_code
  {
    double key1;
    double key2;
    std::string key3;
  };
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char > &s);
    ~iofmtguard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}
#endif //SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
