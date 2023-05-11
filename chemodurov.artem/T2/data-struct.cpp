#include "data-struct.hpp"
#include <iostream>
#include "IO-structs.hpp"

namespace chemodurov
{
  std::istream & operator>>(std::istream & in, DataStrct & data)
  {
    if (!checkInSentry(in))
    {
      return in;
    }
    DataStrct res;
    std::string temp;
    bool isKey1 = false;
    bool isKey2 = false;
    bool isKey3 = false;
    in >> DelimiterIO{'('} >> DelimiterIO{':'};
    for (size_t i = 0; i < 3; ++i)
    {
      in >> temp >> DelimiterIO{' '};
      if (temp.substr(0, 3) == "key")
      {
        if (temp[4] == '1' && !isKey1)
        {
          in >> DoubleIO{res.key1};
          isKey1 = true;
        }
        else if (temp[4] == '2' && !isKey2)
        {
          in >> LongLongIO{res.key2};
          isKey2 = true;
        }
        else if (temp[4] == '3' && !isKey3)
        {
          in >> StringIO{res.key3};
          isKey3 = true;
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
        in >> DelimiterIO{':'};
      }
    }
    in >> DelimiterIO{')'};
    if (in)
    {
      data = res;
    }
    return in;
  }
}
