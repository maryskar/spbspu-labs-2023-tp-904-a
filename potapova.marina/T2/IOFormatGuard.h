#include <iostream>
#include <iomanip>

namespace potapova
{
  class IOFormatGuard
  {
    public:
      IOFormatGuard(std::basic_ios< char >& stream);
      ~IOFormatGuard();
    private:
      std::basic_ios< char >& stream_;
      char fill_character_;
      std::basic_ios< char >::fmtflags format_flags_;
  };
}
