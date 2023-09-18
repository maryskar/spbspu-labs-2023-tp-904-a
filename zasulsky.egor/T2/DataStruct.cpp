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
  iofmtguard ofmtguard(out);
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
  double k1 = 0.0;
  long long k2 = 0;
  std::string k3 = "";
  in >> DelimiterIO{ '(' };

  for (size_t i = 0; i < 3; i++)
  {
    in >> DelimiterIO{ ':' } >> LabelIO{ "key" };
    in >> d;

    switch (d)
    {
    case 1:
    {
      if (key1)
      {
        in >> DblIO{ k1 };
        key1 = false;
      }
      break;
    }
    case 2:
    {
      if (key2)
      {
        in >> SllIO{ k2 };
        key2 = false;
      }
      break;
    }
    case 3:
    {
      if (key3)
      {
        in >> StringIO{ k3 };
        key3 = false;
      }
      break;
    }
    default:
    {
      in.setstate(std::ios::failbit);
      break;
    }
    }
  }
  in >> LabelIO{ ":)" };
  ref  = dataStruct{ k1, k2, k3 };
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
      return rhs.key3.size() > lhs.key3.size();
    }
    return rhs.key2 > lhs.key2;
  }
  else
  {
    return 0;
  }
}
