#include "iotypes.hpp"

namespace hrushchev
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

  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest)
  {
  	std::istream::sentry sentry(in);
  	if (!sentry)
  	{
  		return in;
  	}
  	return in >> dest.num;
  }

  std::istream& operator>>(std::istream& in, ComplexIO&& dest)
  {
  	std::istream::sentry sentry(in);
  	if (!sentry)
  	{
  		return in;
  	}
  	in >> DelimiterIO{'#'} >> DelimiterIO{'c'} >> DelimiterIO{'('}; 
  	in >> dest.real >> DelimiterIO{' '} >> dest.imag >> DelimiterIO{')'};
  	return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.str, '"');
  }
}
