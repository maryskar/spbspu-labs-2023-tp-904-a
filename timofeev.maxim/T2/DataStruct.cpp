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







    std::istream &operator>>(std::istream &in, Data &dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        Data input;
        {
            using sep = DelimiterIO;
            using label = LabelIO;
            using dbl = DoubleIO;
            using str = StringIO;
            in >> sep{ '{' };
            in >> label{ "key1" } >> sep{ ':' } >> dbl{ input.key1 };
            in >> sep{ ',' };
            in >> label{ "key2" } >> sep{ ':' } >> str{ input.key2 };
            in >> sep{ '}' };
        }
        if (in)
        {
            dest = input;
        }
        return in;
    }

    std::ostream &operator<<(std::ostream &out, const Data &src)
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