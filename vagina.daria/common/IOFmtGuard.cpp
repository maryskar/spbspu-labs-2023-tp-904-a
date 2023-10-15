#include "IOFmtGuard.h"

vagina::iofmtguard::iofmtguard(std::basic_ios< char >& s):
  s_(s),
  fill_(s.fill()),
  fmt_(s.flags())
{}

vagina::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.flags(fmt_);
}
