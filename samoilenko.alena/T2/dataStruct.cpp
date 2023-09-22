#include "dataStruct.h"
#include "iotypes.h"

bool samoilenko::compareData(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  else if (lhs.key2 != rhs.key2)
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
    for (size_t k = 0; k <= 2; k++)
    {
      size_t num = 0;
      in >> Label{"key"} >> num;
      if (num == 1)
      {
        in >> Ull{inp.key1} >> Delimiter{':'};
      }
      if (num == 2)
      {
        in >> ComplexNum{inp.key2} >> Delimiter{':'};
      }
      if (num == 3)
      {
        in >> String{inp.key3} >> Delimiter{':'};
      }
      if (!sentry)
      {
        return in;
      }
    }
    if (in)
    {
      dest = inp;
    }
    return in;
  }
}

std::istream& samoilenko::operator<<(std::istream& out, const DataStruct& src)
{

}