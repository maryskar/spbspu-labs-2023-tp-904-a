#include "DataStruct.h"

#include <iomanip>
#include <limits>

#include "FormatGuard.h"
#include "TypesIO.h"

using DataStruct = ganiullin::DataStruct;

std::istream& ganiullin::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  double inputKey1 = 0;
  unsigned long long inputKey2 = 0;
  std::string inputKey3 = "";
  {
    using sep = ganiullin::DelimiterIO;
    using label = ganiullin::LabelIO;
    using dbl = ganiullin::DoubleI;
    using str = ganiullin::StringIO;
    using ull = ganiullin::ULongLongIO;

    in >> sep{'('};
    bool isKey1 = false;
    bool isKey2 = false;
    bool isKey3 = false;
    while (!(isKey1 && isKey2 && isKey3) && in.good()) {
      size_t labelNum = 0;
      in >> sep{':'} >> label{"key"} >> labelNum;

      switch (labelNum) {
      case 1:
        if (isKey1) {
          in.setstate(std::ios::failbit);
        }
        in >> dbl{inputKey1};
        isKey1 = true;
        break;
      case 2:
        if (isKey2) {
          in.setstate(std::ios::failbit);
        }
        in >> ull{inputKey2};
        isKey2 = true;
        break;
      case 3:
        if (isKey3) {
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
  if (in) {
    dest = DataStruct{inputKey1, inputKey2, inputKey3};
  }
  return in;
}

std::ostream& ganiullin::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  ganiullin::iofmtguard fmtguard(out);

  out << "(:";
  out << "key1" << ' ' << ganiullin::DoubleO{src.key1} << ':';
  out << "key2" << ' ' << "0x" << std::hex << std::uppercase << src.key2 << ':';
  out << "key3" << ' ' << '"' << src.key3 << '"' << ':';
  out << ')';
  return out;
}

bool ganiullin::Comparator::operator()(const DataStruct& lhs, const DataStruct rhs) const
{
  if (lhs.key1 == rhs.key1){
    if (lhs.key2 == rhs.key2) {
      return lhs.key3.length() < rhs.key3.length();
    }
    return lhs.key2 < rhs.key2;
  }
  return lhs.key1 < rhs.key1;
};
