#include "data_struct.hpp"
#include "IO.hpp"
#include "iofmtguard.hpp"

bool zhuravlev::compareData(const DataStruct& lhs, const DataStruct& rhs)
{
  return (lhs.key1 != rhs.key1) ? (lhs.key1 < rhs.key1): (lhs.key2 != rhs.key2) ? (lhs.key2 < rhs.key2): (lhs.key3.size() < rhs.key3.size());
}
