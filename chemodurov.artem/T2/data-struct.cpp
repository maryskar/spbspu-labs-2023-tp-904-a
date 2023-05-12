#include "data-struct.hpp"
#include <iostream>
#include <iomanip>
#include "IO-structs.hpp"
#include "iofmtguard.hpp"

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
    in >> DelimiterIO{'('};
    for (size_t i = 0; i < 3; ++i)
    {
      in >> LabelIO{temp};
      if (temp.substr(0, 3) == "key")
      {
        if (temp[3] == '1' && !isKey1)
        {
          in >> DoubleIO{res.key1};
          isKey1 = true;
        }
        else if (temp[3] == '2' && !isKey2)
        {
          in >> LongLongIO{res.key2};
          isKey2 = true;
        }
        else if (temp[3] == '3' && !isKey3)
        {
          in >> StringIO{res.key3};
          isKey3 = true;
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
      }
    }
    in >> DelimiterIO{':'} >> DelimiterIO{')'};
    if (in)
    {
      data = res;
    }
    return in;
  }

  std::ostream & operator<<(std::ostream & out, const DataStrct & data)
  {
    if (!checkOutSentry(out))
    {
      return out;
    }
    std::string temp;
    std::ostringstream str(temp);
    str << std::scientific << std::setprecision(1) << data.key1;
    temp = str.str();
    size_t e_ind = temp.find('e');
    temp.erase(temp.begin() + e_ind + 2);
    out << '(';
    out << ":key1 " << temp;
    out << ":key2 " << data.key2 << "ll";
    out << ":key3 \"" << data.key3;
    out << "\":)";
    return out;
  }

  bool checkOutSentry(std::ostream & out)
  {
    std::ostream::sentry sentry(out);
    return static_cast< bool >(sentry);
  }

  bool isLess(const DataStrct & lhs, const DataStrct & rhs)
  {
    bool fst = lhs.key1 < rhs.key1;
    return fst || (lhs.key1 == rhs.key1 && lhs.key2 < rhs.key2) || (lhs.key2 == rhs.key2 && lhs.key3.size() < rhs.key3.size());
  }
}
