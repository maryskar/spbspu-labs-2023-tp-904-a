#include "IOFormatGuard.h"

potapova::IOFormatGuard::IOFormatGuard(std::basic_ios< char >& stream):
  stream_(stream),
  fill_character_(stream.fill()),
  format_flags_(stream.flags())
{

}

potapova::IOFormatGuard::~IOFormatGuard()
{
  stream_.fill(fill_character_);
  stream_.flags(format_flags_);
}
