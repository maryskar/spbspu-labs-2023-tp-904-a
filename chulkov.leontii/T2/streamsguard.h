#ifndef STREAMSGUARD_H
#define STREAMSGUARD_H
#include <ios>

namespace chulkov {
  class StreamGuard {
  public:
    explicit StreamGuard(std::basic_ios< char >& stream);
    ~StreamGuard();

  private:
    std::basic_ios< char >& st_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
