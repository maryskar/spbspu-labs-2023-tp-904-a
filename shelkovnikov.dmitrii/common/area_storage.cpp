#include "area_storage.h"
dimkashelk::AreaStorage::AreaStorage():
  area(0.0)
{}
double dimkashelk::AreaStorage::operator()(const dimkashelk::Point &lnr, const dimkashelk::Point &rnl)
{
  area += std::abs(lnr.x * rnl.y - rnl.x * lnr.y) / 2;
  return area;
}
