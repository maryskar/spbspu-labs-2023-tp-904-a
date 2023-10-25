#ifndef IOSTRUCT_H
#define IOSTRUCT_H
#include <string>

namespace chulkov {
  struct UllIO {
    unsigned long long& ref;
  };

  struct CharIO {
    char& ref;
  };

  struct LabelIO {
    std::string exp;
  };

  struct StringIO {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, UllIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
