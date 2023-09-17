#include "DataIO.h"
#include <string>
#include <iostream>
namespace zhukova
{
  std::istream & operator>>(std::istream & in, DelimiterIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '\0';
    in >> c;
    if (in && (c != dest.value))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream & operator>>(std::istream & in, ComplexIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    double re = 0.0;
    double im = 0.0;
    in >> LabelIO{"#c("} >> re >> im >> DelimiterIO{')'};
    dest.value = std::complex< double >(re, im);
    return in;
  }
  std::istream & operator>>(std::istream & in, RationalIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    long long natural = 0;
    unsigned long long fraction = 0;
    in >> LabelIO{"(:N"} >> natural >> LabelIO{":D"} >> fraction >> LabelIO{":)"};
    dest.value = std::pair< long long, unsigned long long >(natural, fraction);
    return in;
  }
  std::istream & operator>>(std::istream & in, StringIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.value, '"');
  }
  std::istream & operator>>(std::istream & in, LabelIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '\0';
    for (size_t i = 0; i < dest.value.length(); i++)
    {
      in >> c;
      if (in && (c != dest.value[i]))
      {
        in.setstate(std::ios::failbit);
        break;
      }
    }
    return in;
  }
  std::istream & operator>>(std::istream & in, DataStruct & dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    using sep = DelimiterIO;
    using label = LabelIO;
    using comp = ComplexIO;
    using rat = RationalIO;
    using str = StringIO;
    in >> sep{'('};
    for (size_t i = 0; i < 3; i++)
    {
      in >> label{":key"};
      char number = '\0';
      in >> number;
      if (in)
      {
        if (number == '1')
        {
          in >> comp{input.key1};
        }
        else if (number == '2')
        {
          in >> rat{input.key2};
        }
        else if (number == '3')
        {
          in >> str{input.key3};
        }
      }
    }
    in >> sep{':'};
    in >> sep{')'};
    if (in)
    {
      dest = input;
    }
    return in;
  }
  std::ostream & operator<<(std::ostream & out, const std::complex< double > & src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    out << "#c(" << src.real() << ' ' << src.imag() << ')';
    return out;
  }
  std::ostream & operator<<(std::ostream & out, const std::pair< long long, unsigned long long > & src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    out << "(:N " << src.first << ":D " << src.second << ":)";
    return out;
  }
  std::ostream & operator<<(std::ostream & out, const DataStruct & src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << '(';
    out << ":key1 " << std::fixed << std::setprecision(1) << src.key1;
    out << ":key2 " << src.key2;
    out << ":key3 \"" << src.key3 << '\"';
    out << ":)";
    return out;
  }
  iofmtguard::iofmtguard(std::basic_ios< char > & s):
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {
  }
  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}
