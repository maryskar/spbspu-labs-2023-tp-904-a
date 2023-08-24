#include "dataStruct.h"

bool fesenko::compare(const DataStruct &first, const DataStruct &second)
{
  if (first.key1 != second.key1) {
    return first.key1 < second.key1;
  } else if (first.key2 != second.key2) {
    return first.key2 < second.key2;
  } else {
    return first.key3.length() < second.key3.length();
  }
}
