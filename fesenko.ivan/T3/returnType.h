#ifndef RETURNTYPE_H
#define RETURNTYPE_H
#include <ostream>
namespace fesenko
{
  struct ReturnType
  {
   public:
    explicit ReturnType(size_t value);
    explicit ReturnType(double value);
    explicit ReturnType(bool value);
    char getReturnType() const;
    size_t getUnsigned() const;
    double getDouble() const;
    bool getBool() const;
   private:
    union
    {
      size_t uns;
      double db;
      bool bl;
    } value_;
    char type_;
  };
  std::ostream &operator<<(std::ostream &out, const ReturnType &rt);
}
#endif
