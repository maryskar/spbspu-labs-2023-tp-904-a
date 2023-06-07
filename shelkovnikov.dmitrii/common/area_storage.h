#ifndef SPBSPU_LABS_2023_TP_904_AREASTORAGE_H
#define SPBSPU_LABS_2023_TP_904_AREASTORAGE_H
#include "point.h"
namespace dimkashelk
{
  struct AreaStorage
  {
    double operator()(const Point &lnr, const Point &rnl);
  };
}
#endif
