#include "DataStruct.hpp"
#include "InpOutTypes.hpp"

std::ostream& operator<<(std::ostream& out, const dataStruct& ref)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  for (int i = 1; i < 4; i++)
  {
    out << DelimiterIO{ '(' } << DelimiterIO{ ':' } << "key" << i << DelimiterIO{ ' ' } << ref.key1;
  }
  return out << DelimiterIO{ ':' } << DelimiterIO{ ')' };
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
    return in;
  }
}
