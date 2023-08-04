#include "datastruct.hpp"
#include "iofmtguard.hpp"
#include "typesio.hpp"

bool gulyaev::isLess(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 < rhs.key1) {
    return true;
  } else if (lhs.key1 > rhs.key1) {
    return false;
  }
  if (std::abs(lhs.key2) < std::abs(rhs.key2)) {
    return true;
  } else if (std::abs(lhs.key2) > std::abs(rhs.key2)) {
    return false;
  }
  if (lhs.key3 < rhs.key3) {
    return true;
  } else if (lhs.key3 > rhs.key3) {
    return false;
  }
  return false;
}
std::istream &gulyaev::operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterIO;
    using bin = BinUnsignedLongLongI;
    using cmp = ComplexI;
    using str = StringIO;
    in >> sep{'('} >> sep{':'};
    if (in) {
      bool key1 = false;
      bool key2 = false;
      bool key3 = false;
      for (int i = 0; i < 3; ++i) {
        std::string temp = "";
        in >> temp;
        if (temp == "key1" && !key1) {
          in >> bin{input.key1};
          key1 = true;
        } else if (temp == "key2" && !key2) {
          in >> cmp{input.key2};
          key2 = true;
        } else if (temp == "key3" && !key3) {
          in >> str{input.key3};
          key3 = true;
        } else {
          in.setstate(std::ios::failbit);
          break;
        }
      }
    }
    in >> sep{')'};
  }
  if (in)
  {
    dest = input;
  }
  return in;
}
std::ostream &gulyaev::operator<<(std::ostream &out, const DataStruct &dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:key1 " << BinUnsignedLongLongO{dest.key1};
  out << ":key2 " << ComplexO{dest.key2}; 
  out << ":key3 \"" << dest.key3 << "\":)";
  return out;
}
