#include "streamguard.h"

dmitriev::StreamGuard::StreamGuard(std::basic_ios< char >& stream):
  m_stream(stream),
  m_fill(stream.fill()),
  m_precision(stream.precision()),
  m_fmt(stream.flags())
{}

dmitriev::StreamGuard::~StreamGuard()
{
  m_stream.fill(m_fill);
  m_stream.precision(m_precision);
  m_stream.flags(m_fmt);
}
