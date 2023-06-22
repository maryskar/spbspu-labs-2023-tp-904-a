#ifndef T2_STREAM_GUARD_H
#define T2_STREAM_GUARD_H

#include <ios>

namespace kumachev {
  class StreamGuard {
  public:
    explicit StreamGuard(std::basic_ios< char > &s);
    ~StreamGuard();

  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
