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

  struct ProcessingState {
    bool key1;
    bool key2;
    bool key3;
  };

  struct CharIO {
    char value;
  };

  struct FieldIO {
    std::string &value;
  };

  struct StringIO {
    std::string &value;
  };

  struct UnsignedLongLongIO {
    unsigned long long &value;
  };

  struct PairIO {
    std::pair< long long, unsigned long long > &value;
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

  static void processField(std::istream &istream, const std::string &field, T2::DataStruct &dataStruct,
                           T2::ProcessingState &state);

  std::istream &operator>>(std::istream &istream, T2::DataStruct &dataStruct);
  static std::istream &operator>>(std::istream &istream, T2::CharIO &&character);
  static std::istream &operator>>(std::istream &istream, T2::FieldIO &&field);
  static std::istream &operator>>(std::istream &istream, T2::StringIO &&field);
  static std::istream &operator>>(std::istream &istream, T2::UnsignedLongLongIO &&unsignedLongLong);
  static std::istream &operator>>(std::istream &istream, T2::PairIO &&pair);
}

#endif //T2_DATA_STRUCT_H
