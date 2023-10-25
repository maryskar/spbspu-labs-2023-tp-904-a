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

char fesenko::ReturnType::getReturnType() const
{
  return type_;
}

size_t fesenko::ReturnType::getUnsigned() const
{
  return value_.uns;
}

double fesenko::ReturnType::getDouble() const
{
  return value_.db;
}

bool fesenko::ReturnType::getBool() const
{
  return value_.bl;
}

std::ostream &fesenko::operator<<(std::ostream &out, const ReturnType &rt)
{
  if (rt.getReturnType() == 'u') {
    out << rt.getUnsigned();
  } else if (rt.getReturnType() == 'd') {
    out << std::fixed << std::setprecision(1) << rt.getDouble();
  } else if (rt.getReturnType() == 'b') {
    out << (rt.getBool() ? "<TRUE>" : "<FALSE>");
  }
  return out;
}
