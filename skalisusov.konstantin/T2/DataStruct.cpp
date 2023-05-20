#include "DataStruct.h"
namespace skalisusov
{
  std::istream &operator>>(std::istream &in, DataStruct &dest)
  {
    std::istream::sentry CheckSentry(in);
    if(!CheckSentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using cover = CoverIO;
      using dubsci = DoubleSciencificFormatI;
      using dublit = DoubleLiteralFormatIO;
      using str = StringIO;
      std::string keyNum = "";
      in >> sep{'('};
      in >> sep{':'};
      for(size_t i = 0; i < 3; i++)
      {
        in >> keyNum;
        if(keyNum == "key1")
        {
          in >> dublit {input.key1_} >> sep{':'};
        }
        else if(keyNum == "key2" )
        {
          in >> dubsci{input.key2_} >> sep{':'};
        }
        else if(keyNum == "key3" )
        {
          in >> str{input.key3_} >> sep{':'};
        }
      }
      in >> sep{')'};
    }
    if(in)
    {
      dest = input;
    }
    return in;
  }
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest)
  {
    std::ostream::sentry CheckSentry(out);
    if(!CheckSentry)
    {
      return out;
    }
    iofmtguard iofmtguard(out);
    out << "(";
    out << ":key1 " << std::fixed << std::setprecision(1) << dest.key1_ << 'd';
    out << ":key2 " << DoubleSciencificFormatO{dest.key2_};
    out << ":key3 " << '"' << dest.key3_ << '"';
    out << ":)";
    return out;
  }
}