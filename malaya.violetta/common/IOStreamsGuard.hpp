#ifndef T2_IOSTREAMSGUARD_HPP
#define T2_IOSTREAMSGUARD_HPP
#include <ios>
namespace malaya
{
  class IOStreamsGuard
  {
   public:
    explicit IOStreamsGuard(std::basic_ios< char > & stream);
    ~IOStreamsGuard();
   private:
    std::basic_ios< char > & stream_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}
#endif
