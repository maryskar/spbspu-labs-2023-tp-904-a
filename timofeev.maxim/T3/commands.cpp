#include "commands.h"
#include <istream>
#include <exception>
#include "helpFunctions.h"
#include "../common/IofGuard.h"
namespace timofeev
{
  void doAreaCommands (std::istream &in, )
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return;
    }
    std::string secPart;
    in >> secPart;
    if (is_number(secPart))
    {
      //do smth with vertexes
    }
    else if (secPart == "EVEN")
    {
      doEven();
    }
    else if (secPart == "ODD")
    {
      doOdd();
    }
    else
    {
      throw std::logic_error("Error");
    }
  }

}