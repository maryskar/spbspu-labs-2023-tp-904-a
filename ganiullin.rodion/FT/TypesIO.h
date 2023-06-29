#ifndef TYPES_IO_H
#define TYPES_IO_H

#include <string>

namespace ganiullin {
  struct DelimiterIO {
    char exp;
  };
  struct DoubleI {
    double& ref;
  };
  struct DoubleO {
    const double val;
  };
  struct StringIO {
    std::string& ref;
  };
  struct LabelIO {
    std::string exp;
  };
  struct ULongLongIO {
    unsigned long long& ref;
  };
  struct WordIO {
    std::string& ref;
  };
  struct EntryI {
    std::string& ref;
    size_t& val;
  };
  std::istream& operator>>(std::istream& in, EntryI&& dest);
  std::istream& operator>>(std::istream& in, WordIO&& dest);
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, DoubleI&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, ULongLongIO&& dest);

  std::ostream& operator<<(std::ostream& out, const DoubleO&& dest);
}
#endif
