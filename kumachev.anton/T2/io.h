#ifndef T2_IO_H
#define T2_IO_H

#include <string>
#include <ios>
#include "data_struct.h"

namespace kumachev {
  struct FieldIO {
    std::string &value;
  };

  struct StringIO {
    std::string &value;
  };

  struct UnsignedLongLongIO {
    unsigned long long &value;
  };

  struct RationalIO {
    rational &value;
  };

  std::istream &operator>>(std::istream &istream, DataStruct &dataStruct);
  std::istream &operator>>(std::istream &istream, FieldIO &&field);
  std::istream &operator>>(std::istream &istream, StringIO &&field);
  std::istream &operator>>(std::istream &istream, UnsignedLongLongIO &&ullIO);
  std::istream &operator>>(std::istream &istream, RationalIO &&rationalIO);

  std::ostream &operator<<(std::ostream &ostream, const DataStruct &dataStruct);
}

#endif
