#ifndef PRED_COMP_HPP
#define PRED_COMP_HPP

#include <string>

#include "data-types.hpp"

namespace turkin
{
  struct isSameTRNS
  {
    public:
      explicit isSameTRNS(const std::string & trns);
      bool operator()(const word_pair_t & trns);
    private:
      std::string trns_;
  };
}

#endif
