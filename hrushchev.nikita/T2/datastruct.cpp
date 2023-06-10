#include "datastruct.hpp"
#include <complex>
#include <string>
#include "scopeguard.hpp"

namespace hrushchev
{
  bool Comparator::operator()(const DataStruct& lhs, const DataStruct& rhs) const
  {
  	if (lhs.key1 != rhs.key1)
  	{
  		return lhs.key1 < rhs.key1;
  	}
  	else
  	{
  		if (lhs.key2 != rhs.key2)
  		{
  			return std::abs(lhs.key2) < std::abs(rhs.key2);
  		}
  		return lhs.key3.length() < lhs.key3.length();
  	}
  }

  std::istream& operator>>(std::istream& in, DataStruct& data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    iofmtguard fmtguard(in);
    unsigned long long key1 = 0;
    std::complex< double > key2(0.0, 0.0);
    std::string key3 = "";
    bool isKey1 = false;
    bool isKey2 = false;
    bool isKey3 = false;
    for (size_t i = 0; i < 3; ++i)
    {
      std::string key;
      in >> LabelIO{key};
    }
  }
}
