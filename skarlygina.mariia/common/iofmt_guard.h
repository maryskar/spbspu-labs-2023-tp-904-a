#ifndef IOFMT_GUARD_H
#define IOFMT_GUARD_H
#include <ios>

class Iofmtguard
{
public:
  Iofmtguard(std::basic_ios< char >& st);
  ~Iofmtguard();
private:
  std::basic_ios< char >& st_;
  char fill_;
  std::streamsize precision_;
  std::basic_ios< char >::fmtflags fmt_;
};

#endif

