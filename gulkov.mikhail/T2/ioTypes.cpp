#include "ioTypes.hpp"

namespace gulkov {
  std::istream& operator>>(std::istream& in, DelimiterIO&& delimeter_io)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (c != delimeter_io.delimeter && in)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& ull_io)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    if (in >> ull_io.ullref)
    {
      return in;
    }
    in.setstate(std::ios::failbit);
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& string_io)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, string_io.string, '"');
  }

  std::istream& operator>>(std::istream& in, CharIO&& char_io)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> gulkov::DelimiterIO{'\''} >> char_io.charref >> DelimiterIO{'\''};
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& label_io)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    for (size_t i = 0; i < label_io.label.length(); i++)
    {
      in >> DelimiterIO{label_io.label[i]};
    }
    return in;
  }
}
