#include "pred-comp.hpp"

turkin::isSameTRNS::isSameTRNS(const std::string & trns):
  trns_(trns)
{}

bool turkin::isSameTRNS::operator()(const word_pair_t & trns)
{
  return trns.second == trns_;
}
