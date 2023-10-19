#include "dataStruct.hpp"
#include "iofmtguard.hpp"
#include "iotypes.hpp"


namespace gulkov {
  bool Comparator::operator()(const DataStruct& data1, const DataStruct& data2)
  {
    if (data1.key1 == data2.key1) {
      if (data1.key2 == data2.key2) {
        return data1.key3.length() < data2.key3.length();
      }
      return data1.key2 < data2.key2;
    } else {
      return data1.key1 < data2.key1;
    }
  }

  std::istream& operator>>(std::istream& in, DataStruct& data)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    DataStruct input;
    {
      using delimeter = DelimiterIO;
      using label = LabelIO;
      using chr = CharIO;
      using string = StringIO;
      in >> delimeter{'('};
      for (int i = 1; i <= 3; i++) {
        in >> label{":key"};
        size_t num = 0;
        in >> num;
        if (num == 1) {
          in >> UnsignedLongLongIO{input.key1};
        } else if (num == 2) {
          in >> chr{input.key2};
        } else if (num == 3) {
          in >> string{input.key3};
        }
        if (!sentry) {
          return in;
        }
      }
      in >> delimeter{':'} >> delimeter{')'};
    }
    if (in) {
      data = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& data)
  {
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }
    iofmtguard guard(out);
    out << "(:";
    out << "key1 " << data.key1 << ":";
    out << "key2"
        << " '" << data.key2 << "':";
    out << "key3 \"" << data.key3 << "\":)";
    return out;
  }
}
