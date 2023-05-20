#include "DataStruct.h"
namespace skalisusov
{
  std::istream &operator>>(std::istream &in, DataStruct &dest)
  {
    std::istream::sentry CheckSentry(in);
    if(!CheckSentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using cover = CoverIO;
      using dubsci = DoubleSciencificFormatI;
      using dublit = DoubleLiteralFormatIO;
      using str = StringIO;

  }
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest)
  {
    std::ostream::sentry CheckSentry(out);
    if(!CheckSentry)
    {
      return out;
    }
    iofmtguard iofmtguard(out);
    out << "(";
    out << ":key1 " << std::fixed << std::setprecision(1) << dest.key1_ << 'd';
    out << ":key2 " << DoubleSciencificFormatO{dest.key2_};
    out << ":key3 " << '"' << dest.key3_ << '"';
    out << ":)";
    return out;
  }
}