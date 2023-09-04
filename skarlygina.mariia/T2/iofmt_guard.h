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

Iofmtguard::Iofmtguard(std::basic_ios< char >& st) :
  st_(st),
  fill_(st.fill()),
  precision_(st.precision()),
  fmt_(st.flags())
{}

Iofmtguard::~Iofmtguard()
{
  st_.fill(fill_);
  st_.precision(precision_);
  st_.flags(fmt_);
}

#endif

