#include "streamsguard.h"

namespace chulkov {
  StreamGuard::StreamGuard(std::basic_ios< char >& st):
    st_(st),
    fill_(st.fill()),
    precision_(st.precision()),
    fmt_(st.flags())
  {}

  StreamGuard::~StreamGuard()
  {
    st_.fill(fill_);
    st_.precision(precision_);
    st_.flags(fmt_);
  }
}
