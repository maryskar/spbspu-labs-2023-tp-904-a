#include "data_struct.hpp"
#include <iomanip>
#include <vector>
#include <iterator>
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
    double input_key1 = 0;
    unsigned long long input_key2 = 0;
    std::string input_key3 = "";
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using dbl = DoubleI;
      using str = StringIO;
      using ullh = ULLHexIO;
      in >> sep{ '(' } >> sep { ':' };
      for (size_t i = 1; i <= 3; i++)
      {
        size_t num = 0;
        in >> label{ "key" } >> num;
        if (num == 1)
        {
          in >> dbl{ input_key1 } >> sep { ':' };
        }
        else if (num == 2)
        {
          in >> ullh{ input_key2 } >> sep { ':' };
        }
        else if (num == 3)
        {
          in >> str{ input_key3 } >> sep { ':' };
        }
      }
      if (input_key1 == 0)
      {
        in.setstate(std::ios::failbit);
      }
      if (in)
      {
        dest = DataStruct{input_key1, input_key2, input_key3};
      }
      return in;
    }
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
    out << ":key1 " << DoubleO { src.key1 };
    out << ":key2 0x" << std::hex << std::uppercase << src.key2;
    out << ":key3 \"" << src.key3;
    out << "\":)";
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
