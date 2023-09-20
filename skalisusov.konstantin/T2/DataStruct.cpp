#include "DataStruct.h"
#include <iomanip>
#include "iofmtguard.h"
#include "StructTypes.h"

std::istream & skalisusov::operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double key1 = 0.0;
  double key2 = 0.0;
  std::string key3 = "";
  {
    using delim = DelimiterIO;
    using dublit = DoubleLiteralFormatIO;
    using dubsci = DoubleSciencificFormatI;
    using str = StringIO;
    using label = LabelIO;
    in >> delim{ '(' };
    in >> delim{ ':' };
    for (std::size_t i = 1; i <= 3; i++)
    {
      std::size_t number = 0;
      in >> label{"key"};
      in >> number;
      if (number == 1)
      {
        in >> dublit{ key1 } >> delim{ ':' };
      }
      else if (number == 2)
      {
        in >> dubsci{ key2 } >> delim{ ':' };
      }
      else if (number == 3)
      {
        in >> str{ key3 } >> delim{ ':' };
      }
    }
    in >> delim{')'};
  }
  if (in)
  {
    dest.key1 = key1;
    dest.key2 = key2;
    dest.key3 = key3;
  }
  return in;
}
std::ostream & skalisusov::operator<<(std::ostream &out, const DataStruct &dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard iofmtguard(out);
  using scien = DoubleSciencificFormatO;
  out << "(";
  out << ":key1 " << std::fixed << std::setprecision(1) << dest.key1 << 'd';
  out << ":key2 " << scien{dest.key2};
  out << ":key3 " << '"' << dest.key3 << '"';
  out << ":)";
  return out;
}
bool skalisusov::comparator(const skalisusov::DataStruct &firDs, const skalisusov::DataStruct &secDs)
{
  if (firDs.key1 == secDs.key1)
  {
    if (firDs.key2 == secDs.key2)
    {
      return firDs.key3 < secDs.key3;
    }
    else
    {
      return firDs.key2 < secDs.key2;
    }
  }
  else
  {
    return firDs.key1 < secDs.key1;
  }
}
