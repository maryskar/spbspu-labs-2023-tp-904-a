#ifndef STREAMSTUFF_H
#define STREAMSTUFF_H
#include <iostream>

namespace kozyrin {
  struct DelimiterIO {
    char chr;
  };

  struct LabelIO {
    std::string str;
  };

  struct DoubleIO {
    double& val;
  };

  struct UllIO {
    unsigned long long& val;
  };

  struct StringIO {
    std::string& str;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, UllIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
