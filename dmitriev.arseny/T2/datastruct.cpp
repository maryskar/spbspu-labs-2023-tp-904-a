#include "datastruct.h"
#include <iostream>
#include <customtypes.h>
#include <streamguard.h>

bool dmitriev::compareDataStructures(const DataStruct& lhs, const DataStruct& rhs)
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
    return lhs.key3.length() < rhs.key3.length();
  }
}

std::istream& dmitriev::operator>>(std::istream& inp, DataStruct& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  DataStruct input;
  inp >> SeparatorIO{'('} >> SeparatorIO{':'};
  for (size_t i = 0; i < 3; i++)
  {
    size_t number = 0;
    inp >> LableIO{"key"} >> number;

    switch (number)
    {
    case 1:
      inp >> DoubleI{input.key1} >> SeparatorIO{':'};
      break;
    case 2:
      inp >> LongLongI{input.key2} >> SeparatorIO{':'};
      break;
    case 3:
      inp >> StringI{input.key3} >> SeparatorIO{':'};
      break;
    default:
      inp.setstate(std::ios::failbit);
      break;
    }
    if (!sentry)
    {
      return inp;
    }
  }
  if (inp)
  {
    data = input;
  }

  return inp;
}

std::ostream& dmitriev::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard streamGuard(out);

  out << LableIO{"(:key1 "} << DoubleO{data.key1};
  out << LableIO{":key2 "} << LongLongO{data.key2};
  out << LableIO{":key3 "} << StringO{data.key3} << LableIO{":)"};

  return out;
}
