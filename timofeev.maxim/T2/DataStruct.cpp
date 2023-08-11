#include "DataStruct.h"
#include <iomanip>
#include "IofGuard.h"
/*std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
std::istream &operator>>(std::istream &in, DoubleIO &&dest);
std::istream &operator>>(std::istream &in, ComplexIO &&dest);
std::istream &operator>>(std::istream &in, StringIO &&dest);
std::istream &operator>>(std::istream &in, LabelIO &&dest);
std::istream &operator>>(std::istream &in, DataStruct &dest);
std::ostream &operator<<(std::ostream &out, const DataStruct &dest);*/
namespace timofeev
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
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

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO {'"'}, dest.ref, '"');
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

  std::istream& operator>>(std::istream& in, ComplexIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    using sep = DelimiterIO;
    using lbl = LabelIO;
    using complex = std::complex< double >;
    double real = 0.0;
    double imag = 0.0;
    in >> lbl{"#c("} >> real >> imag >> sep{')'};
    dest.cmp = complex(real, imag);
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
      using dbl = DoubleIO;
      using str = StringIO;
      using cmp = ComplexIO;
      in >> sep{'('} >> sep{':'};
      for (int i = 0; i < 3; i++)
      {
        std::string key;
        in >> key;
        if (key == "key1")
        {
          in >> dbl{input.key1} >> DelimiterIO{':'};
        }
        else if (key == "key2")
        {
          in >> cmp{input.key2} >> DelimiterIO{':'};
        }
        else if (key == "key3")
        {
          in >> str{input.key3} >> DelimiterIO{':'};
        }
        else
        {
          in.setstate(std::ios::failbit);
          return in;
        }
      }
    }
    in >> DelimiterIO{')'};
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const DataStruct &dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 " << dest.key1;
    out << std::fixed;
    out << std::setprecision(1);
    out << ":key2 #c(" << dest.key2.real() << " " << dest.key2.imag() << ")";
    out << ":key3 \"" << dest.key3 << "\":)";
    return out;
  }
}
