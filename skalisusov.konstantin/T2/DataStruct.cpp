#include <iomanip>
#include "DataStruct.h"
#include "StructTypes.h"
#include "iofmtguard.h"

std::istream & skalisusov::operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry CheckSentry(in);
  if(!CheckSentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterIO;
    using dublit = DoubleLiteralFormatIO;
    using dubsci = DoubleSciencificFormatI;
    using str = StringIO;
    using label = LabelIO;
    std::size_t number = 0;
    in >> sep{'('};
    in >> sep{':'};
    for(std::size_t i = 1; i <= 3; i++)
    {
      in >> label{"key"};
      in >> number;
      if(number == 1)
      {
        in >> dublit{input.key1_} >> sep{':'};
      }
      else if(number == 2)
      {
        in >> dubsci{input.key2_} >> sep{':'};
      }
      else if(number == 3)
      {
        in >> str{input.key3_} >> sep{':'};
      }
      number = 0;
    }
    in >> sep{')'};
  }
  if(in)
  {
    dest = input;
  }
  return in;
}
std::ostream & skalisusov::operator<<(std::ostream &out, const DataStruct &dest)
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
bool skalisusov::comparate(const DataStruct &firDs, const DataStruct &secDs)
{
  if(firDs.key1_ != secDs.key1_)
  {
    return firDs.key1_ < secDs.key1_;
  }
  if(firDs.key1_ == secDs.key1_ && firDs.key2_ != secDs.key2_)
  {
    return firDs.key2_ < secDs.key2_;
  }
  else
  {
    return  firDs.key3_.length() < secDs.key3_.length();
  }
}
