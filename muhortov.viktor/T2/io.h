#ifndef IO_H
#define IO_H
#include <iostream>
#include <complex>
#include <string>
#include "iomanip"
#include "dataSrtuct.h"

namespace muhortov {
  struct delimeterIO {
    char chr;
  };

  struct complexIO {
    std::complex< double > &num;
  };

  struct rationalNumIO {
    std::pair< long long, unsigned long long > &num;
  };

  struct stringIO {
    std::string &str;
  };

  struct labelIO {
    std::string str;
  };

  class iofmtquard {
  public:
    explicit iofmtquard(std::basic_ios< char > &s);
    ~iofmtquard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream &operator>>(std::istream &input, delimeterIO &&dest);
  std::istream &operator>>(std::istream &input, complexIO &&dest);
  std::istream &operator>>(std::istream &input, rationalNumIO &&dest);
  std::istream &operator>>(std::istream &input, stringIO &&dest);
  std::istream &operator>>(std::istream &input, labelIO &&dest);
  std::istream &operator>>(std::istream &input, dataStruct &dest);
  std::ostream &operator<<(std::istream &output, std::complex< double > &c);
  std::ostream &operator<<(std::istream &output, std::pair< long long, unsigned long long > &c);
  std::ostream &operator<<(std::ostream &output, const dataStruct &src);
}

#endif
