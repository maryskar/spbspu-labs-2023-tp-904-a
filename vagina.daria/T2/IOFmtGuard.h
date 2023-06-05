#ifndef T2_IOFMTGUARD_H
#define T2_IOFMTGUARD_H
#include <iostream>

namespace vagina
{
  class iofmtguard
  {
  public:
    explicit iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
