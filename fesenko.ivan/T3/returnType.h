#ifndef RETURNTYPE_H
#define RETURNTYPE_H
#include <ostream>
namespace fesenko
{
  struct ReturnType
  {
    explicit ReturnType(size_t num);
    explicit ReturnType(double num);

    union
    {
      size_t uns;
      double db;
    } num_;
    char type_;
  };
  std::ostream &operator<<(std::ostream &out, const ReturnType &rt);
}
#endif
