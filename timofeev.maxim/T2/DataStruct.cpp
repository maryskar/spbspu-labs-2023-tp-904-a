#include "DataStruct.h"
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include "IofGuard.h"
namespace timofeev
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
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

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    for (size_t i = 0; i < dest.exp.size(); i++)
    {
      in >> DelimiterIO{dest.exp[i]};
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, ComplexIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    using sep = DelimiterIO;
    using lbl = LabelIO;
    using complex = std::complex< double >;
    double real = 0.0;
    double imag = 0.0;
    in >> lbl{"#c("} >> real >> imag >> sep{')'};
    dest.cmp = complex(real, imag);
    return in;
  }

  std::istream & operator>>(std::istream & in, DoubleIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    int integer = 0;
    int fractional = 0;
    int power = 0;
    in >> integer >> DelimiterIO{'.'};
    in >> fractional >> DelimiterIO{'e'};
    in >> power;
    double temp = static_cast< double >(fractional) / 10;
    double exp = integer + temp;
    dest.ref = exp * std::pow(10, power);
    return in;
  }
  std::string getScientificDouble(double val)
  {
    std::string res;
    int power = 0;
    if (std::abs(val) > 9 )
    {
      while (std::abs(val) > 9)
      {
        val /= 10;
        power++;
      }
    }
    else if (val == 0)
    {
      res = "0.0";
    }
    else if (std::abs(val) < 1 )
    {
      while (std::abs(val) < 1 )
      {
        val *= 10;
        --power;
      }
    }
    val *= 10;
    int temp = std::round(val);
    res = std::to_string(temp);
    res.insert(1, 1, '.');
    res.append("e");
    if (power > 0)
    {
      res.append("+");
      res.append(std::to_string(power));
    }
    else if (power == 0)
    {
      return res;
    }
    else
    {
      res.append(std::to_string(power));
    }
    return res;
  }

  std::istream &operator>>(std::istream &in, DataStruct &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using dbl = DoubleIO;
      using str = StringIO;
      using cmp = ComplexIO;
      in >> sep{'('} >> sep{':'};
      for (int i = 0; i < 3; i++)
      {
        std::string key;
        in >> key;
        if (key == "key1")
        {
          in >> dbl{input.key1} >> DelimiterIO{':'};
        }
        else if (key == "key2")
        {
          in >> cmp{input.key2} >> DelimiterIO{':'};
        }
        else if (key == "key3")
        {
          in >> str{input.key3} >> DelimiterIO{':'};
        }
        else
        {
          in.setstate(std::ios::failbit);
          return in;
        }
      }
    }
    in >> DelimiterIO{')'};
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const DataStruct &dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 " << getScientificDouble(dest.key1);
    out << std::fixed;
    out << std::setprecision(1);
    out << ":key2 #c(" << dest.key2.real() << " " << dest.key2.imag() << ")";
    out << ":key3 \"" << dest.key3 << "\":)";
    return out;
  }
}
