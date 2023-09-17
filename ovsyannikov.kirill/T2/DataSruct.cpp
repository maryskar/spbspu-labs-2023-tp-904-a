#include "DataStruct.h"

#include <iomanip>
#include <limits>

#include "FormatGuard.h"
#include "TypesIO.h"

using DataStruct = ovsyannikov::DataStruct;

std::istream& ovsyannikov::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  unsigned long long inputKey1 = 0;
  char inputKey2 = 0;
  std::string inputKey3 = "";
  {
    using sep = ovsyannikov::DelimiterIO;
    using label = ovsyannikov::LabelIO;
    using chr = ovsyannikov::CharIO;
    using str = ovsyannikov::StringIO;
    using ull = ovsyannikov::ULongLongIO;

    in >> sep{'('};
    bool isKey1 = false;
    bool isKey2 = false;
    bool isKey3 = false;
    while (!(isKey1 && isKey2 && isKey3) && in.good())
    {
      size_t labelNum = 0;
      in >> sep{':'} >> label{"key"} >> labelNum;

      switch (labelNum)
      {
      case 1:
        if (isKey1)
        {
          in.setstate(std::ios::failbit);
        }
        in >> ull{inputKey1};
        isKey1 = true;
        break;
      case 2:
        if (isKey2)
        {
          in.setstate(std::ios::failbit);
        }
        in >> chr{inputKey2};
        isKey2 = true;
        break;
      case 3:
        if (isKey3)
        {
          in.setstate(std::ios::failbit);
        }
        in >> str{inputKey3};
        isKey3 = true;
        break;
      default:
        in.setstate(std::ios::failbit);
        break;
      }
    }
    in >> sep{':'};
    in >> sep{')'};
  }
  if (in)
  {
    dest = DataStruct{inputKey1, inputKey2, inputKey3};
  }
  return in;
}

std::ostream& ovsyannikov::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  ovsyannikov::iofmtguard fmtguard(out);

  out << "(:";
  out << "key1" << ' ' << "0x" << std::hex << std::uppercase << src.key1 << ':';
  out << "key2" << " '" << src.key2 << "':";
  out << "key3" << ' ' << '"' << src.key3 << '"' << ':';
  out << ')';
  return out;
}

bool ovsyannikov::Comparator::operator()(const DataStruct& data1, const DataStruct& data2) const
{
  if (data1.key1 == data2.key1)
  {
    if (data1.key2 == data2.key2)
    {
      return data1.key3.length() < data2.key3.length();
    }
    return data1.key2 < data2.key2;
  }
  return data1.key1 < data2.key1;
}
