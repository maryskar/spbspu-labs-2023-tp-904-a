#include "streamguard.h"

dmitriev::StreamGuard::StreamGuard(std::basic_ios<char>& stream):
  m_stream(stream),
  m_fill(stream.fill()),
  m_precision(stream.precision()),
  m_flags(stream.flags())
{}
