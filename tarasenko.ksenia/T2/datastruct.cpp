#include "datastruct.h"
#include <iostream>
#include "structs_io.h"
#include "iofmtguard.h"
#include "convert_to_bin.h"

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
    bool key1_was = false;
    bool key2_was = false;
    bool key3_was = false;
    in >> sep{'('} >> sep{':'};
    while (in && !(key1_was && key2_was && key3_was))
    {
      char buf[5];
      std::cin.get(buf, 5);
      std::string s(buf);
      if (s.substr(0, 3) != "key")
      {
        in.setstate(std::ios::failbit);
      }
      switch (s[3])
      {
        case '1':
        {
          in >> ull{input.key1} >> sep{':'};
          key1_was = true;
          break;
        }
        case '2':
        {
          in >> ullbin{input.key2} >> sep{':'};
          key2_was = true;
          break;
        }
        case '3':
        {
          in >> str{input.key3} >> sep{':'};
          key3_was = true;
          break;
        }
        default:
          in.setstate(std::ios::failbit);
      }
    }
    in >> sep{')'};
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
  out << "key2" << " " << "0b0" << convertToBin(src.key2) << ":";
  out << "key3" << " " << '"' << src.key3 << '"';
  out << ":)";
  return out;
}
