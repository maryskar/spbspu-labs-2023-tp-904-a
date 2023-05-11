#include "IO-structs.hpp"
#include <iostream>

namespace chemodurov
{
  bool checkSentry(std::istream & in)
  {
    std::istream::sentry sentry(in);
    return static_cast<bool>(sentry);
  }

  std::istream & operator>>(std::istream & in, DelimiterIO && dest)
  {
    if (!checkSentry(in))
    {
      return in;
    }
    char c = '\0';
    in >> c;
    if (in && c != std::tolower(dest.exp) && c != std::toupper(dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream & operator>>(std::istream & in, DoubleIO && dest)
  {
    if (!checkSentry(in))
    {
      return in;
    }
    return in >> std::scientific >> dest.ref;
  }

  std::istream & operator>>(std::istream & in, LongLongIO && dest)
  {
    if (!checkSentry(in))
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{'l'} >> DelimiterIO{'l'};
  }

  std::istream & operator>>(std::istream & in, StringIO && dest)
  {
    if (!checkSentry(in))
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }

  std::istream & operator>>(std::istream & in, LabelIO && dest)
  {
    if (!checkSentry(in))
    {
      return in;
    }
    std::string data;
    if ((in >> StringIO{data} && data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
