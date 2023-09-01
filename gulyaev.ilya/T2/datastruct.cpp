#include "datastruct.hpp"
#include "iofmtguard.hpp"
#include "typesio.hpp"

bool gulyaev::isLess(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 != rhs.key1) {
    return (lhs.key1 < rhs.key1);
  }
  if (std::abs(lhs.key2) != std::abs(rhs.key2)) {
    return (std::abs(lhs.key2) < std::abs(rhs.key2));
  }
  return lhs.key3 < rhs.key3;
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
      bool keys[] = {0, 0, 0};
      for (int i = 0; i < 3; ++i) {
        std::string temp = "";
        in >> temp;
        if (temp == "key1" && !keys[0]) {
          in >> bin{input.key1};
          keys[0] = true;
        } else if (temp == "key2" && !keys[1]) {
          in >> cmp{input.key2};
          keys[1] = true;
        } else if (temp == "key3" && !keys[2]) {
          in >> str{input.key3};
          keys[2] = true;
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
