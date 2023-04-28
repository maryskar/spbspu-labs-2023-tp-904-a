#ifndef T2_DATA_STRUCT_H
#define T2_DATA_STRUCT_H

#include <string>
#include <ios>
#include <bits/stl_pair.h>

namespace T2 {
  struct DataStruct {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  struct CharIO {
    char value;
  };

  struct FieldIO {
    std::string value;
  };

  struct LiteralIO {
    unsigned long long value;
  };

  struct PairIO {
    std::pair< long long, unsigned long long > value;
  };

  struct StringIO {
    std::string value;
  };

  class StreamGuard {
  public:
    explicit StreamGuard(std::basic_ios< char > &s);
    ~StreamGuard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream &operator>>(std::istream &istream, T2::DataStruct &dataStruct);
  static std::istream &operator>>(std::istream &istream, T2::CharIO &&character);
  static std::istream &operator>>(std::istream &istream, T2::FieldIO &&field);
  static std::istream &operator>>(std::istream &istream, T2::LiteralIO &&literal);
  static std::istream &operator>>(std::istream &istream, T2::PairIO &&pair);
  static std::istream &operator>>(std::istream &istream, T2::StringIO &&string);
}

#endif //T2_DATA_STRUCT_H
