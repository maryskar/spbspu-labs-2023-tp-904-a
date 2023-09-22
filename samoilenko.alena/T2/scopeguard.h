#ifndef SCOPEGUARD_H
#define SCOPEGUARD_H
#include <ios>
namespace samoilenko
{
  class iofmtguard
  {
  public:
    explicit iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  };
}

#endif
