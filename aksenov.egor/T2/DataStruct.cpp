#include "DataStruct.h"
#include "Iofmtguard.h"
namespace aksenov
{
  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    for (size_t i = 0; i < dest.exp.size(); i++) {
      in >> DelimiterIO {dest.exp[i]};
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, ComplexIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    double real = 0.0;
    double imag = 0.0;
    in >> LabelIO{"#c("} >> real >> imag >> DelimiterIO{')'};
    dest.complex = std::complex< double >(real, imag);
    return in;
  }

  std::istream &operator>>(std::istream &in, UllIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string str = "";
    std::getline(in, str, ':');
    dest.ref = std::strtoull(str.c_str(), 0, 16);
    return in;
  }

  std::istream &operator>>(std::istream &in, DataStruct &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    iofmtguard iofmtguard(in);

    bool isKey3 = false;
    bool isKey2 = false;
    bool isKey1 = false;
    unsigned long long key1 = 0.0;
    std::complex< double > key2(0.0, 0.0);
    std::string key3 = "";
    in >> LabelIO{"(:"};
    for (size_t i = 0; i < 3; ++i)
    {
      std::string key;
      in >> key;
      if (!isKey1 && key == "key1")
      {
        in >> UllIO{key1};
        isKey1 = true;
      }
      else if (!isKey2 && key == "key2")
      {
        in >> ComplexIO{key2} >> DelimiterIO{':'};
        isKey2 = true;
      }
      else if (!isKey3 && key == "key3")
      {
        in >> StringIO{key3} >> DelimiterIO{':'};
        isKey3 = true;
      }
      else
      {
        in.setstate(std::ios::failbit);
        return in;
      }
    }
    in >> DelimiterIO{')'};
    dest = DataStruct{key1, key2, key3};
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const HexFormat &hex)
  {
    out << "(:key1 " << "0x" << std::hex << std::uppercase << hex.hex << ":";
    return out;
  }

  std::ostream &operator<<(std::ostream &out, const DataStruct &dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    HexFormat hex{dest.key1};
    out << hex;
    out << std::fixed << std::setprecision(1);
    out << "key2 " << "#c(" << dest.key2.real() << " " << dest.key2.imag() << "):";
    out << "key3 \"" << dest.key3 << "\":)";
    return out;
  }
}
