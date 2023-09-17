#include "DataStruct.hpp"
#include "InpOutTypes.hpp"
#include "Iofmtguard.hpp"

std::ostream& operator<<(std::ostream& out, const dataStruct& ref)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(:key1 " << convertToSci(ref.key1);
  out << ":key2 " << ref.key2 << "ll";
  out << ":key3 " << '"' << ref.key3 << '"' << ":" << ")";
  return out;
}

std::istream& operator>>(std::istream& in, dataStruct& ref)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  iofmtguard iofmtguard(in);
  int d = 0;
  bool key1 = true;
  bool key2 = true;
  bool key3 = true;
  dataStruct res{0.0,0,""};
  in >> DelimiterIO{ '(' };

  for (size_t i = 0; i < 3; i++)
  {
    in >> DelimiterIO{ ':' } >> LabelIO{ "key" };
    in >> d;

    switch (d)
    {
    case 1:
      if(key1)
      {
      in >>  std::fixed >> std::setprecision(1) >> std::scientific  >> res.key1;
      key1 = false;
      }
      break;

    case 2:
      if (key2)
      {
      in >> res.key2 >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
      key2 = false;
      }
      break;

    case 3: 
      if (key3)
      {
        in >> StringIO{ res.key3 };
        key3 = false;
      }
      break;

    default:
      in.setstate(std::ios::failbit);
      break;
    }
  }
  in >> LabelIO{ ":)" };
  ref = res;
  return in;
}

bool compare(dataStruct& lhs, dataStruct& rhs)
{
  if (rhs.key1 > lhs.key1)
  {
    return 1;
  }
  else if (lhs.key1 == rhs.key1)
  {
    if (lhs.key2 == rhs.key2)
    {
      return rhs.key3 > lhs.key3;
    }
    return rhs.key2 > lhs.key2;
  }
  else
  {
    return 0;
  }
}
