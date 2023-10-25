#include "streamGuard.h"

aristarkhov::StreamGuard::StreamGuard(std::basic_ios< char >& stream):
  stream_(stream),
  fill_(stream.fill()),
  precision_(stream.precision()),
  flags_(stream.flags())
{
}

aristarkhov::StreamGuard::~StreamGuard()
{
  stream_.fill(fill_);
  stream_.precision(precision_);
  stream_.flags(flags_);
}
