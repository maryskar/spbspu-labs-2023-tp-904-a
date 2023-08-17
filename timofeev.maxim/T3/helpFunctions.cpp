#include "helpFunctions.h"
#include <iterator>
namespace timofeev
{
  bool is_number(const std::string& s)
  {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
  }
  void doEven()
  {

  }
  void doOdd();
  void doMaxArea();
  void doMaxV();
  void doMinArea();
  void doMinV();
  void doСountEven();
  void doCountOdd();
}