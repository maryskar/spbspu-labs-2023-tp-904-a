#include "returnType.h"
#include <iomanip>

fesenko::ReturnType::ReturnType(size_t value):
  value_({ .uns = value }),
  type_('u')
{}

fesenko::ReturnType::ReturnType(double value):
  value_({ .db = value }),
  type_('d')
{}

fesenko::ReturnType::ReturnType(bool value):
  value_({ .bl = value }),
  type_('b')
{}

std::ostream &fesenko::operator<<(std::ostream &out, const ReturnType &rt)
{
  if (rt.type_ == 'u') {
    out << rt.value_.uns;
  } else if (rt.type_ == 'd') {
    out << std::fixed << std::setprecision(1) << rt.value_.db;
  } else if (rt.type_ == 'b') {
    out << (rt.value_.bl ? "<TRUE>" : "<FALSE>");
  }
  return out;
}
