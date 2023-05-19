#include "data_struct.hpp"
#include <iomanip>
#include "IO_structs.hpp"
#include "iofmtguard.hpp"
namespace kotova
{
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
      using dbl = DoubleIO;
      using str = StringIO;
      using ullh = ULLHexIO;
      in >> sep{ '(' };
      in >> label{ "key1" } >> sep{ ':' } >> dbl{ input.key1 };
      in >> sep{ ',' };
      in >> label{ "key2" } >> sep{ ':' } >> ullh{ input.key2 };
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
    out << "(: ";
    out << "key1 " << std::fixed << std::setprecision(2) << src.key1;
    out << ":key2 0f0" << src.key2;
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
  }
}
