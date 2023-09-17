#include "dataStruct.h"
#include <string>
#include <iomanip>
#include <bitset>
#include "IOFormatGuard.h"

namespace potapova
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char sym = '0';
    in >> sym;
    if (in && (sym != dest.sign))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, UnsignedLongIntOctIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> std::oct >> dest.oct;
  }

  std::istream& operator>>(std::istream& in, UnsignedLongIntBinIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char sec_value = '0';
    return in >> DelimiterIO{'0'} >> sec_value;
    if (sec_value != 'b' || sec_value != 'B')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::bitset< 64 > binary = 0;
    in >> binary;
    if (in.fail())
    {
      return in;
    }
    dest.bin = binary.to_ullong();
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.str, '"');
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{data}) && (data != dest.value))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      in >> DelimiterIO{'('};
      in >> DelimiterIO{':'};
      while (in)
      {
        if (in >> LabelIO{"key1"})
        {
          in >> UnsignedLongIntOctIO{input.key1};
        }
        else if (in >> LabelIO{"key2"})
        {
          in >> UnsignedLongIntBinIO{input.key2};
        }
        else
        {
          in >> StringIO{input.key3};
        }
        in >> DelimiterIO{':'};
      }
      in >> DelimiterIO{')'};
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, DataStruct& source)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    IOFormatGuard format_guard(out);
    out << "(:";
    out << "key1 " << source.key1 << ":";
    out << "key2 " << source.key2 << ":";
    out << "key3 " << source.key3 << ":";
    out << ")";
    return out;
  }

  bool Comparator::operator()(const DataStruct& that, const DataStruct& other)
  {
    if (that.key1 == other.key1)
    {
      if (that.key2 == other.key2)
      {
        return that.key3.length() < other.key3.length();
      }
      return that.key2 < other.key2;
    }
    else
    {
      return that.key1 < other.key1;
    }
  }
}
