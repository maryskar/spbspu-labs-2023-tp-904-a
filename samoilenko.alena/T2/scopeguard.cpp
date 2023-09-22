#include "scopeguard.h"

samoilenko::iofmtguard::iofmtguard(std::basic_ios< char >& s):
  s_ (s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{}                                                              
