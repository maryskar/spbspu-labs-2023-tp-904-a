#include "returnType.h"
#include <iomanip>

fesenko::ReturnType::ReturnType(size_t num):
  num_({ .uns = num }),
  type_('u')
{}

fesenko::ReturnType::ReturnType(double num):
  num_({ .db = num }),
  type_('d')
{}

std::ostream &fesenko::operator<<(std::ostream &out, const ReturnType &rt)
{
  if (rt.type_ == 'u') {
    out << rt.num_.uns;
  } else if (rt.type_ == 'd') {
    out << std::fixed << std::setprecision(1) << rt.num_.db;
  }
  return out;
}
