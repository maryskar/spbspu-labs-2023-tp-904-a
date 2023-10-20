#include "data_struct.h"
#include <iostream>
#include <iofmt_guard.h>
#include <struct_io.h>

bool skarlygina::operator<(const DataStruct& left, const DataStruct& right)
{
  if (left.key1 == right.key1)
  {
    if (left.key2 == right.key2)
    {
      return left.key3.length() < right.key3.length();
    }
    return left.key2 < right.key2;
  }
  return left.key1 < right.key1;
}

std::ostream& skarlygina::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sent(out);
  if (!sent)
  {
    return out;
  }
  Iofmtguard fmtguard(out);
  out << "(:key1 " << DBLsciO{data.key1};
  out << ":key2 " << ULLhexO{data.key2};
  out << ":key3 " << '"' << data.key3 << '"' << ":)";
  return out;
}

std::istream& skarlygina::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  DataStruct in_data = {0.0, 0, ""};
  in >> DelimiterSep{'('} >> DelimiterSep{':'};
  for (int i = 0; i < 3; ++i)
  {
    std::string keyX = "";
    in >> keyX;
    if (keyX == "key1")
    {
      in >> DBLsciI{in_data.key1};
    }
    else if (keyX == "key2")
    {
      in >> ULLhexI{in_data.key2};
    }
    else if (keyX == "key3")
    {
      in >> StringIO{in_data.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    in >> DelimiterSep{':'};
  }
  in >> DelimiterSep{')'};
  if (in)
  {
    data = in_data;
  }
  return in;
}
