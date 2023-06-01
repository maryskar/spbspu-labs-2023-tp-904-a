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
    std::string string;
    in >> string;
    std::istringstream inn(string);
    using sep = DelimiterIO;
    using label = LabelIO;
    using dbl = DoubleIO;
    using str = StringIO;
    using ullh = ULLHexIO;
    in >> sep{ '(' } >> sep { ':' };
    if (!in)
    {
      return in;
    }
    for (size_t i = 0; i < 3; i++)
    {
      size_t num = 0;
      in >> label{ "key" } >> num;
      if (num == 1)
      {
        inn >> dbl{ input.key1 } >> sep { ':' };
      }
      else if (num == 2)
      {
        in >> ullh{ input.key2 } >> sep { ':' };
      }
      else if (num == 3)
      {
        in >> str{ input.key3 } >> sep { ':' };
      }
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
    out << ":key2 0x" << src.key2;
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
  }

  bool check(const DataStruct &lhs, const DataStruct &rhs)
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    return (lhs.key2 != rhs.key2) ? lhs.key2 < rhs.key2 : lhs.key3.length() < rhs.key3.length();
  }
}
