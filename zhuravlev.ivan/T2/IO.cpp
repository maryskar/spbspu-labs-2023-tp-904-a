#include "IO.hpp"
#include "iofmtguard.hpp"
#include <iomanip>

namespace zhuravlev
{
  std::istream& operator>>(std::istream& in, DelimetrIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.expression))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream& in, BinIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> DelimetrIO{'0b'}  >> dest.ref;
  }

  std::istream &operator>>(std::istream& in, HexIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> DelimetrIO{'0x'}  >> dest.ref;
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimetrIO{ '"' }, dest.ref, '"');
  }

  std::istream &operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.expression))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, DataStruct &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimetrIO;
      using label = LabelIO;
      using dbl = BinIO;
      using hex = HexIO;
      using str = StringIO;
      in >> sep{ '(' };
      in >> label{ "key1" } >> sep{ ':' } >> dbl{ input.key1 };
      in >> sep{ ',' };
      in >> label{ "key2" } >> sep{ ':' } >> hex{ input.key2 };
      in >> sep{ ',' };
      in >> label{ "key3" } >> sep{ ':' } >> str{ input.key3 };
      in >> sep{ ')' };
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
  std::ostream &operator<<(std::ostream &out, const DataStruct &src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(";
    out << ":key1 0b" << src.key1;
    out << ":key2 0x" << std::hex << src.key2;
    out << ":key3 \"" << src.key3;
    out << "\":)";
    return out;
  }
}