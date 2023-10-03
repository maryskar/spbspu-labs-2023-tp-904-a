#ifndef OUT_MSG_HPP
#define OUT_MSG_HPP

#include <fstream>
#include <utility>
#include <string>

namespace turkin
{
  void outInvalidCMD(std::ostream & out);
  void outEmptyCMD(std::ostream & out);
  void outAddedCMD(std::ostream & out);
  void outRemovedCMD(std::ostream & out);
  void outNotFoundedCMD(std::ostream & out);
}

#endif
