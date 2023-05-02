//[CMP LSP] Комплексное число (std::complex< double >) в следующем виде:
//:keyX #c(1.0 -1.0):
//:keyX #c(-1.0 1.0):
//Гарантируется, что вещественная и мнимая часть разделены ровно одним пробелом. При сравнении с другими полями должен быть использован модуль комплексного числа

//[RAT LSP] Рациональное число (std::pair< long long, unsigned long long >) в следующем
//виде:
//:keyX (:N -2:D 3:):
//:keyX (:N 3:D 2:):

#include <iostream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include "data_structs.h"
int main()
{
  using data_struct = dimkashelk::DataStruct;
  std::vector< data_struct > data;
  std::copy(
    std::istream_iterator< data_struct >(std::cin),
    std::istream_iterator< data_struct >(),
    std::back_inserter(data)
  );

  std::cout << "Data:\n";
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< data_struct >(std::cout, "\n")
  );

  return 0;
}

namespace dimkashelk
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    // все перегрузки операторов ввода/вывода должны начинаться с проверки экземпляра класса sentry
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

  std::istream &operator>>(std::istream &in, DoubleIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{ 'd' };
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream &operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
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
      using label = LabelIO;
      using dbl = DoubleIO;
      using str = StringIO;
      in >> sep{ "(:" };
      in >> label{ "key1" } >> sep{ ":" } >> dbl{ input.key1 };
      in >> sep{ ',' };
      in >> label{ "key2" } >> sep{ ':' } >> str{ input.key2 };
      in >> sep{ '}' };
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const DataStruct &src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "{ ";
    out << "\"key1\": " << std::fixed << std::setprecision(1) << src.key1 << "d, ";
    out << "\"key2\": " << src.key2;
    out << " }";
    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios< char > &s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}
