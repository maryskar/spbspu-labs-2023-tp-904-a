#include "dataStruct.h"
#include "scopeGuard.h"
#include "typesIO.h"

std::istream &gudkov::operator>>(std::istream &in, Data &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Data input;
  {
    using sep = DelimiterExpIO;
    in >> sep{ '(' };
    if (in)
    {
      in >> sep{ ':' };
      bool isRead[3] = {};
      for (size_t i = 0; i < 3; ++i)
      {
        std::string str = "";
        in >> LabelIO{ str };
        if (str == "key1")
        {
          if (isRead[0])
          {
            in.setstate(std::ios::failbit);
          }
          else
          {
            in >> LongLongIO{ input.key1 };
            isRead[0] = true;
          }
        }
        else if (str == "key2")
        {
          if (isRead[1])
          {
            in.setstate(std::ios::failbit);
          }
          else
          {
            in >> UnsignedLongLongIO{ input.key2 };
            isRead[1] = true;
          }
        }
        else if (str == "key3")
        {
          if (isRead[2])
          {
            in.setstate(std::ios::failbit);
          }
          else
          {
            in >> StringIO{ input.key3 };
            isRead[2] = true;
          }
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
        in >> sep{ ':' };
      }
      in >> sep{ ')' };
    }
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream &gudkov::operator<<(std::ostream &out, const Data &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(:";
  out << "key1 " << src.key1 << "ll";
  out << ":";
  out << "key2 " << src.key2 << "ull";
  out << ":";
  out << "key3 " << "\"" << src.key3 << "\"";
  out << ":)";
  return out;
}

bool gudkov::isLess(const Data &lhs, const Data &rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.length() < rhs.key3.length();
}
