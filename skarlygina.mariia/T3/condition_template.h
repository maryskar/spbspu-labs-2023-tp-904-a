#ifndef CONDITION_TEMPLATE_H
#define CONDITION_TEMPLATE_H
#include "help_structures.h"
#include "help_commands.h"
namespace skarlygina
{
  template< class Condition >
  struct AreaCondition
  {
    AreaCondition(Condition cond):
      condition(cond)
    {}

    double operator()(double area, const Polygon& poly)
    {
      if (condition(poly))
      {
        return area + findAreaPoly(poly);
      }
      return area;
    }
  private:
    Condition condition;
  };
}
#endif
