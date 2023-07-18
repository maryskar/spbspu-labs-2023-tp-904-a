#ifndef T3_SCOPEGUARD_HPP
#define T3_SCOPEGUARD_HPP
#include <iostream>
namespace litvin
{
  class ScopeGuard
  {
   public:
    explicit ScopeGuard(std::basic_ios< char > & s);
    ~ScopeGuard();
   private:
    std::basic_ios< char > & s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}
#endif
