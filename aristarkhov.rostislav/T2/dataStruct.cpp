#include <iomanip>
#include <iostream>

#include "dataStruct.h"
#include "streamGuard.h"
#include "iostruct.h"

std::istream& aristarkhov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  in >> DelimiterIO{'('} >> DelimiterIO{':'};
  for (int i = 0; i < 3; i++)
  {
    std::string key{};
    size_t num = 0;
    in >> LabelIO{"key"} >> num;
    if (key == "key1")
    {
      in >> CharIO{input.key1};
    }
    else if (key == "key2")
    {
      in >> RationalNumberIO{input.key2};
    }
    else if (key == "key3")
    {
      in >> StringIO{input.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> DelimiterIO{':'};
  }
  in >> DelimiterIO{')'};
  return in;
}

std::ostream& aristarkhov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard streamGuard(out);
  out << "(:key1 " << std::setprecision(1) << data.key1;
  out << ":key2 \'" << std::setprecision(0) << "\'";
  out << ":key3 \"" << std::quoted(data.key3) << "\":)";
  return out;
}

bool aristarkhov::compare(const DataStruct& first, const DataStruct& second)
{
  if (first.key1 == second.key1)
  {
    if (first.key2 == second.key2)
    {
      return (first.key3 < second.key3);
    }
    return (first.key2 < second.key2);
  }
  return (first.key1 < second.key1);
}
