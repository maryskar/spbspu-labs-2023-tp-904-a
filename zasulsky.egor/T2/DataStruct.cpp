#include "DataStruct.hpp"
#include "InpOutTypes.hpp"

std::ostream& operator<<(std::ostream& out, const dataStruct& ref)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(:key1 " << std::scientific << ref.key1;
  out << ":key2 " << ref.key2 << "ll";
  out << ":key3 " << ref.key3 << ":" << ")";
  return out;
}

std::istream& operator>>(std::istream& in, dataStruct& ref)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c;
  in >> DelimiterIO{ '(' };

  for (size_t i = 0; i < 3; i++)
  {
    in >> DelimiterIO{ ':' } >> LabelIO{ "key" };
    in >> c;
    in >> DelimiterIO{ ' ' };
    switch (c)
    {
    case '1':
    {
      in >> ref.key1;
      break;
    }
    case '2':
    {
      in >> ref.key2;
      break;
    }
    case '3':
    {
      in >> ref.key3;
      break;
    }
    }
    in >> DelimiterIO{ ':' };
    in >> DelimiterIO{ ')' };
  }
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
