#include "area_storage.h"
double dimkashelk::AreaStorage::operator()(const dimkashelk::Point &lnr, const dimkashelk::Point &rnl)
{
  return lnr.x * rnl.y - rnl.x * lnr.y;
}
