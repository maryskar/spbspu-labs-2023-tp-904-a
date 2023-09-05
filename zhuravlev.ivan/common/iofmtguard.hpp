#ifndef SPBSPU_LABS_2023_TP_904_A_IOFMTGUARD_HPP
#define SPBSPU_LABS_2023_TP_904_A_IOFMTGUARD_HPP
#include <iostream>

namespace zhuravlev
{
  class iofmtguard
  {
  public:
    explicit iofmtguard(std::basic_ios< char > &s);
    ~iofmtguard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
  };
}
#endif
