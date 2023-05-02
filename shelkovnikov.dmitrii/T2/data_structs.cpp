#include "data_structs.h"
namespace dimkashelk
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, ComplexIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{ 'd' };
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream &operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, complex_type &&c)
  {
    using sep = DelimiterIO;
    double real = 0.0;
    double imaginative = 0.0;
    in >> sep{'('} >> real >> imaginative >> sep{')'};
    c = std::complex< double >(real, imaginative);
    return in;
  }
  std::istream &operator>>(std::istream &in, rational_number &&c)
  {
    using sep = DelimiterIO;
    long long first = 0;
    unsigned long long second = 0;
    in >> sep{'('} >> sep{':'} >> sep{'N'} >> first >> sep{':'} >> sep{'D'} >> second >> sep{':'} >> sep{')'};
    c = rational_number{first, second};
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
      using sep = DelimiterIO;
      using label = LabelIO;
      using str = StringIO;
      in >> sep{'('} >> sep{':'};
      in >> label{"key1"} >> sep{'#'} >> sep{'c'} >> complex_type{ input.key1 };
      in >> sep{ ':' };
      in >> label{"key2"} >> sep{':'} >> rational_number{ input.key2 };
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
    out << "{ ";
    out << "\"key1\": " << std::fixed << std::setprecision(1) << src.key1 << "d, ";
    out << "\"key2\": " << src.key2;
    out << " }";
    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios< char > &s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}
