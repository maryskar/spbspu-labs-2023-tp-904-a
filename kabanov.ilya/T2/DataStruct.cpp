#include "DataStruct.hpp"

#include "TypesIO.hpp"
#include "FormatGuardIO.hpp"

std::istream& kabanov::operator>>(std::istream& in, kabanov::DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  unsigned long long key1 = 0;
  char key2 = '0';
  std::string key3 = "";
  {
    in >> kabanov::DelimiterIO{ '(' };
    bool isKey1 = false;
    bool isKey2 = false;
    bool isKey3 = false;
    for (std::size_t i = 0; i < 3; ++i)
    {
      size_t labelNum = 0;
      in >> kabanov::DelimiterIO{ ':' } >> kabanov::LabelIO{ "key" } >> labelNum;

      switch (labelNum)
      {
      case 1:
        if (isKey1)
        {
          in.setstate(std::ios::failbit);
        }
        in >> kabanov::ULongLongBinI{ key1 };
        isKey1 = true;
        break;
      case 2:
        if (isKey2)
        {
          in.setstate(std::ios::failbit);
        }
        in >> kabanov::CharIO{ key2 };
        isKey2 = true;
        break;
      case 3:
        if (isKey3)
        {
          in.setstate(std::ios::failbit);
        }
        in >> kabanov::StringIO{ key3 };
         isKey3 = true;
        break;
      default:
        in.setstate(std::ios::failbit);
        break;
      }
    }
    in >> kabanov::DelimiterIO{ ':' };
    in >> kabanov::DelimiterIO{ ')' };
  }
  if (in)
  {
    dest = DataStruct{ key1, key2, key3 };
  }
  return in;
}

std::ostream& kabanov::operator<<(std::ostream& out, const kabanov::DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  kabanov::FormatGuardIO guard(out);

  out << "(:key1" << ' ' << kabanov::ULongLongBinO{ src.key1 } << ':';
  out << "key2" << " '" << src.key2 << "':";
  out << "key3" << " \"" << src.key3 << "\":)";
  return out;
}

bool kabanov::comp(const kabanov::DataStruct& lhs, const kabanov::DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  else if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  else
  {
    return lhs.key3.size() < rhs.key3.size();
  }
}
