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
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
  };
}

#endif
