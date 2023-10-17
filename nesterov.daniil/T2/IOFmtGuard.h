#ifndef T2_IOFMTGUARD_H
#define T2_IOFMTGUARD_H

#include <iostream>

namespace nesterov
{
  class IOFmtGuard
  {
  public:
    explicit IOFmtGuard(std::basic_ios< char > &s);
    ~IOFmtGuard();

  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
