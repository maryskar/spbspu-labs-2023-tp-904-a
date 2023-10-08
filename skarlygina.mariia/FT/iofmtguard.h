#ifndef IOFMTGUARD_H
#define IOFMTGUARD_H
#include <ios>

namespace skarlygina
{
  class IofmtGuard
  {
  public:
    explicit IofmtGuard(std::ios& stream);
    ~IofmtGuard();

  private:
    std::ios& str_;
    std::streamsize prec_;
    std::ios::fmtflags flags_;
  };
}
#endif
