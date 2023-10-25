#ifndef IO_H
#define IO_H
#include <iostream>
#include <complex>
#include <string>
#include <iomanip>
#include "dataSrtuct.h"
#include "iofmtguard.h"

namespace muhortov {
  struct delimiterIO {
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

  std::istream &operator>>(std::istream &input, delimiterIO &&dest);
  std::istream &operator>>(std::istream &input, complexIO &&dest);
  std::istream &operator>>(std::istream &input, rationalNumIO &&dest);
  std::istream &operator>>(std::istream &input, stringIO &&dest);
  std::istream &operator>>(std::istream &input, labelIO &&dest);
}

#endif
