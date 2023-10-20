#include "get_abs_complex.h"

namespace shestakov
{
  double getAbsComplex(std::complex< double > complex_number)
  {
    return std::sqrt(std::pow(complex_number.real(), 2.0) + std::pow(complex_number.imag(), 2.0));
  }
}
