#include "commands.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <iofmtguard.h>

namespace azheganova
{
  using namespace std::placeholders;

  std::ostream & printInvalidCommand(std::ostream & out)
  {
    out << "<INVALID COMMAND>";
    return out;
  }
}
