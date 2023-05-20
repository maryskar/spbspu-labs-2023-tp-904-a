#ifndef SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#define SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

namespace skalisusov
{
  struct Data: public std::__1::error_code
  {
    double key1;
    double key2;
    std::string key3;
  };

  std::istream &operator>>(std::istream &in, Data &dest);
  std::ostream &operator<<(std::ostream &out, Data &src);


}
#endif //SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
