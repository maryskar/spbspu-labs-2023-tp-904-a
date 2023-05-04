#ifndef T2_DATA_STRUCT_H
#define T2_DATA_STRUCT_H

#include <string>
#include <ios>

namespace kumachev {
  struct DataStruct {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
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

  std::istream &operator>>(std::istream &istream, DataStruct &dataStruct);
  std::istream &operator>>(std::istream &istream, CharIO &&character);
  std::istream &operator>>(std::istream &istream, FieldIO &&field);
  std::istream &operator>>(std::istream &istream, StringIO &&field);
  std::istream &operator>>(std::istream &istream, UnsignedLongLongIO &&unsignedLongLong);
  std::istream &operator>>(std::istream &istream, PairIO &&pair);

  std::ostream &operator<<(std::ostream &ostream, const DataStruct &dataStruct);

  bool compareData(const DataStruct &lhs, const DataStruct &rhs);
}

#endif //T2_DATA_STRUCT_H
