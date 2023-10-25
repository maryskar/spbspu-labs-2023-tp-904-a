#include "dataStruct.hpp"
#include "iofmtGuard.hpp"
#include "ioTypes.hpp"


namespace gulkov {
  bool Comparator::operator()(const DataStruct& data1, const DataStruct& data2)
  {
    if (data1.key1 == data2.key1)
    {
      if (data1.key2 == data2.key2)
      {
        return data1.key3.length() < data2.key3.length();
      }
      return data1.key2 < data2.key2;
    }
    else
    {
      return data1.key1 < data2.key1;
    }
  }

  std::istream& operator>>(std::istream& in, DataStruct& data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      in >> DelimiterIO{'('};
      for (int i = 1; i <= 3; i++)
      {
        in >> LabelIO{":key"};
        size_t num = 0;
        in >> num;
        if (num == 1)
        {
          in >> DelimiterIO{'0'} >> UnsignedLongLongIO{input.key1};
        } else if (num == 2)
        {
          in >> CharIO{input.key2};
        } else if (num == 3)
        {
          in >> StringIO{input.key3};
        }
      }
      in >> DelimiterIO{':'} >> DelimiterIO{')'};
    }
    if (in)
    {
      data = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& data)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard guard(out);
    out << "(:" << "key1 "<< "0" << data.key1 << ":";
    out << "key2" << " '" << data.key2 << "':";
    out << "key3 \"" << data.key3 << "\":)";
    return out;
  }
}
