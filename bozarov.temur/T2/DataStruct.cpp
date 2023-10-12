#include "DataStruct.hpp"
#include "IOFmtGuard.hpp"
#include "TypesIO.hpp"

bool bozarov::compare(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 != rhs.key1) {
    return (lhs.key1 < rhs.key1);
  }
  if (std::abs(lhs.key2) != std::abs(rhs.key2)) {
    return (std::abs(lhs.key2) < std::abs(rhs.key2));
  }
  return lhs.key3 < rhs.key3;
}
std::istream &bozarov::operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  DataStruct input;
  {
    using del = DelimiterIO;
    using cmp = ComplexI;
    using ull = UnsignedLongLongI;
    using str = StringIO;
    in >> del{'('} >> del{':'};
    if (in) {
      bool keys[] = {0, 0, 0};
      for (int i = 0; i < 3; ++i) {
        std::string temp = "";
        in >> temp;
        if (temp == "key1" && !keys[0]) {
          in >> ull{input.key1} >> del{':'};
          keys[0] = true;
        } else if (temp == "key2" && !keys[1]) {
          in >> cmp{input.key2} >> del{':'};
          keys[1] = true;
        } else if (temp == "key3" && !keys[2]) {
          in >> str{input.key3} >> del{':'};
          keys[2] = true;
        } else {
          in.setstate(std::ios::failbit);
          break;
        }
      }
    }
    in >> del{')'};
  }
  if (in) {
    dest = input;
  }
  return in;
}
std::ostream &bozarov::operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:key1 " << UnsignedLongLongO{src.key1};
  out << ":key2 " << ComplexO{src.key2};
  out << ":key3 \"" << src.key3 << "\":)";
  return out;
}
