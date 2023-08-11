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
}