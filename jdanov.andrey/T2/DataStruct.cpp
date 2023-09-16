#include "DataStruct.h"
#include <algorithm>
#include "IOFormatGuard.h"
#include "ReadIO.h"

bool zhdanov::operator<(const DataStruct& a, const DataStruct& b)
{
  if (a.key1 < b.key1)
    return true;
  if (a.key1 > b.key1)
    return false;
  if (a.key2 < b.key2)
    return true;
  if (a.key2 > b.key2)
    return false;
  if (a.key3.length() < b.key3.length())
    return true;
  if (a.key3.length() > b.key3.length())
    return false;
  return a.key3 < a.key3;
}

std::istream& zhdanov::operator>>(std::istream& input, DataStruct& data)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  IOFormatGuard saverState(input);
  input.unsetf(std::ios::skipws);
  DataStruct temp;
  std::string label = "";
  input >> DelimiterIO{'('};
  input >> DelimiterIO{':'};
  bool checkKey[3] = {false, false, false};
  for (size_t i = 0; i < 3; ++i)
  {
    if (!input.good())
    {
      break;
    }
    input >> WordIO{label};
    if (label == "key1")
    {
      input >> DelimiterIO{' '} >> LongLongIO{temp.key1} >> DelimiterIO{':'};
      checkKey[0] = true;
    }
    else if (label == "key2")
    {
      input >> DelimiterIO{' '} >> BinaryIO{temp.key2};
      checkKey[1] = true;
    }
    else if (label == "key3")
    {
      input >> DelimiterIO{' '} >> StringIO{temp.key3} >> DelimiterIO{':'};
      checkKey[2] = true;
    }
    else
    {
      input.setstate(std::ios::failbit);
    }
  }
  for (size_t i = 0; i < 3; ++i)
  {
    if (!input.good())
    {
      break;
    }
    if (checkKey[i] == false)
    { 
      input.setstate(std::ios::failbit);
    }
  }
  input >> DelimiterIO{')'};
  if (input.good())
  {
    data = temp;
  }
  return input;
}

std::ostream& zhdanov::operator<<(std::ostream& output, const DataStruct& data)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << "(";
  output << ":";
  output << "key1 " << data.key1 << "ll";
  output << ":";
  output << "key2 "
         << "0b" << toBinary(data.key2);
  output << ":";
  output << "key3 "
         << "\"" << data.key3 << "\"";
  output << ":";
  output << ")";
  return output;
}
