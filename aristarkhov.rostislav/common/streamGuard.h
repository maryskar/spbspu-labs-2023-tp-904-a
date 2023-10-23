#ifndef STREAMGUARD_H
#define STREAMGUARD_H

#include <ios>

namespace aristarkhov
{
  class StreamGuard
  {
  public:
    StreamGuard(std::basic_ios< char >& stream);
    ~StreamGuard();

  private:
    std::basic_ios< char >& stream_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}

#endif
