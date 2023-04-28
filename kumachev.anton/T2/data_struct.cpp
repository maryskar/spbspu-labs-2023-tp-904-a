#include "data_struct.h"

T2::StreamGuard::StreamGuard(std::basic_ios< char > &s):
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{
}

T2::StreamGuard::~StreamGuard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
