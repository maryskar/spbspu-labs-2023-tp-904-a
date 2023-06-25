#include "IOStreamsGuard.hpp"
malaya::IOStreamsGuard::IOStreamsGuard(std::basic_ios< char > & stream):
  stream_(stream),
  fill_(stream.fill()),
  precision_(stream.precision()),
  fmt_(stream.flags())
{}
malaya::IOStreamsGuard::~IOStreamsGuard()
{
  stream_.fill(fill_);
  stream_.precision(precision_);
  stream_.flags(fmt_);
}
