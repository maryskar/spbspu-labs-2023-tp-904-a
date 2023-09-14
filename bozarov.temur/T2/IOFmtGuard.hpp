#ifndef T2_IOFMTGUARD_HPP
#define T2_IOFMTGUARD_HPP
#include <ios>

namespace bozarov
{
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char > &s);
    ~iofmtguard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}
#endif
