#include <limits>

#include <iomanip>
#include "DataStruct.h"
#include "FormatGuard.h"
#include "TypesIO.h"

namespace ganiullin {
  constexpr size_t CHARS_TO_IGNORE = std::numeric_limits< std::streamsize >::max();

  std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using dbl = DoubleI;
      using str = StringIO;
      using ull = ULongLongIO;
      in >> sep{'('};
      bool isKey1 = false;
      bool isKey2 = false;
      bool isKey3 = false;
      while (!(isKey1 && isKey2 && isKey3) && !in.eof()) {
        size_t labelNum = 0;
        in >> sep{':'} >> label{"key"} >> labelNum;

        switch (labelNum) {
          case 1:
            if (isKey1) {
              in.setstate(std::ios::failbit);
            }
            in >> dbl{input.key1};
            isKey1 = true;
            break;
          case 2:
            if (isKey2) {
              in.setstate(std::ios::failbit);
            }
            in >> ull{input.key2};
            isKey2 = true;
            break;
          case 3:
            if (isKey3) {
              in.setstate(std::ios::failbit);
            }
            in >> str{input.key3};
            isKey3 = true;
            break;
          default:
            in.setstate(std::ios::failbit);
            break;
        }
        if (in.fail()) {
          in.clear();
          in.ignore(CHARS_TO_IGNORE, '(');
          isKey1 = isKey2 = isKey3 = false;
        }
      }
      in >> sep{':'};
      in >> sep{')'};
    }

    if (in) {
      dest = input;
    }

    return in;
  }
  std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }

    iofmtguard fmtguard(out);
    out << "(:";

    out << "key1" << ' ' << DoubleO{src.key1} << ':';
    out << "key2" << ' ' << "0x" << std::hex << std::uppercase << src.key2 << ':';
    out << "key3" << ' ' << '"' << src.key3 << '"' << ':';
    out << ')';
    return out;
  }

  bool Comparator::operator()(const DataStruct& lhs, const DataStruct rhs) const {
    if (lhs.key1 == rhs.key1) {
      if (lhs.key2 == rhs.key2) {
        return lhs.key3.length() < rhs.key3.length();
      }
      return lhs.key2 < rhs.key2;
    }
    return lhs.key1 < rhs.key1;
  };
}  // namespace ganiullin
