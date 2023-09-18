#include "get_abs_complex.h"

namespace shestakov{
  double getAbsComplex(std::complex< double > complex_number)
  {
    return std::sqrt(pow(complex_number.real(), 2) + pow(complex_number.imag(), 2));
  }
}
