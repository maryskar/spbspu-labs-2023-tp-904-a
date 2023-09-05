#ifndef T2_DATAIO_H
#define T2_DATAIO_H
#include <string>
#include <complex>
#include <iomanip>
#include "DataStruct.h"
namespace zhukova
{
  struct DelimiterIO
  {
    char value;
  };
  struct LabelIO
  {
    std::string value;
  };
  struct ComplexIO
  {
    std::complex< double > & value;
  };
  struct RationalIO
  {
    std::pair< long long, unsigned long long > & value;
  };
  struct StringIO
  {
    std::string & value;
  };
  class iofmtguard
  {
   public:
    iofmtguard(std::basic_ios< char > & s);
    ~iofmtguard();
   private:
    std::basic_ios< char > & s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  std::istream & operator>>(std::istream & in, ComplexIO && dest);
  std::istream & operator>>(std::istream & in, RationalIO && dest);
  std::istream & operator>>(std::istream & in, StringIO && dest);
  std::istream & operator>>(std::istream & in, LabelIO && dest);
  std::istream & operator>>(std::istream & in, DataStruct & dest);
  std::ostream & operator<<(std::ostream & out, const std::complex< double > & src);
  std::ostream & operator<<(std::ostream & out, const std::pair< long long, unsigned long long > & src);
  std::ostream & operator<<(std::ostream & out, const DataStruct & dest);
}
#endif
