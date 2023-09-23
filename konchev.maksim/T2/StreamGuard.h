#ifndef KONCHEV_MAKSIM_STREAMGUARD_H
#define KONCHEV_MAKSIM_STREAMGUARD_H
#include <iostream>
namespace konchev
{
  class StreamGuard
  {
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
