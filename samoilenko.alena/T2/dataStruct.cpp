#include "dataStruct.h"
#include <bitset>
#include <iomanip>
#include "iotypes.h"
#include "scopeguard.h"

bool samoilenko::compareData(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  else if (std::abs(lhs.key2) != std::abs(rhs.key2))
  {
    return std::abs(lhs.key2) < std::abs(rhs.key2);
  }
  else
  {
    return lhs.key3.length() < rhs.key3.length();
  }
}

std::istream& samoilenko::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct inp;
  {
    in >> Delimiter{'('} >> Delimiter{':'};
    for (size_t k = 0; k < 3; k++)
    {
      size_t num = 0;
      in >> Label{"key"} >> num;
      if (num == 1)
      {
        in >> BinUll{inp.key1};
      }
      else if (num == 2)
      {
        in >> ComplexNum{inp.key2} >> Delimiter{':'};
      }
      else if (num == 3)
      {
        in >> String{inp.key3} >> Delimiter{':'};
      }
      else if (!sentry)
      {
        return in;
      }
    }
    in >> Delimiter{')'};
    if (in)
    {
      dest = inp;
    }
  }
  return in;
}

std::ostream& samoilenko::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << '(' << ":key1 ";
  std::string binary = std::bitset< 64 >(src.key1).to_string();
  binary.erase(0, binary.find('1'));
  out << "0b0" << binary;
  out << std::fixed << std::setprecision(1);
  out << ":key2 #c(" << src.key2.real() << " " << src.key2.imag() << ')';
  out << ":key3 \"" << src.key3 << "\":)";
  return out;
}
