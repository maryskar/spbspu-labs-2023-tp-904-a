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

  class iofmtguard
  {
  public:
    explicit iofmtguard(std::basic_ios< char > & s);
    ~iofmtguard();
  private:
    std::basic_ios< char > & s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
