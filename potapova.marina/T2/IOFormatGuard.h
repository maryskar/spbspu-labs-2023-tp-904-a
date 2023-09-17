#include <iostream>
#include <iomanip>

namespace potapova
{
  class IOFormatGuard
  {
    public:
      IOFormatGuard(std::basic_ios< char >& stream):
        stream_(stream),
        fill_character_(stream.fill()),
        format_flags_(stream.flags())
      {

      }

      ~IOFormatGuard()
      {
        stream_.fill(fill_character_);
        stream_.flags(format_flags_);
      }
    private:
      std::basic_ios< char >& stream_;
      char fill_character_;
      std::basic_ios< char >::fmtflags format_flags_;
  };
}
