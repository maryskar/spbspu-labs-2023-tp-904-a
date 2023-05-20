#include "datastruct.h"
#include <iostream>
#include "structs_io.h"
#include "iofmtguard.h"

std::istream& tarasenko::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterIO;
    using label = LabelIO;
    using ull = ULLIO;
    using ullbin = ULLBinIO;
    using str = StringIO;
    //(:key1 10ull:key2 0b0111:key3 "Data":)
    //(:key1 10ull:key2 0B0111:key3 "Data":)
    in >> sep{'('};
    in >> sep{':'} >> label{"key1"} >> ull{input.key1};
    in >> sep{':'} >> label{"key2"} >> ullbin{input.key2};
    in >> sep{':'} >> label{"key3"} >> str{input.key3};
    in >> sep{':'} >> sep{')'};
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream& tarasenko::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:";
  out << "key1" << " " << src.key1 << "ull" << ":";
  out << "key2" << " " << "0b" << src.key2 << ":";
  out << "key3" << " " << '"' << src.key3 << '"';
  out << ":)";
  return out;
}
