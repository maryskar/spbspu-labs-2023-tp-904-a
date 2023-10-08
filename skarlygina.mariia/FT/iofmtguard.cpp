#include "iofmtguard.h"
skarlygina::IofmtGuard::IofmtGuard(std::ios& stream) :
  str_(stream),
  prec_(stream.precision()),
  flags_(stream.flags())
{}

skarlygina::IofmtGuard::~IofmtGuard()
{
  str_.precision(prec_);
  str_.flags(flags_);
}
