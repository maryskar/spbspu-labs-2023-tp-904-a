#include "datastruct.hpp"
#include <complex>
#include <string>

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
}
