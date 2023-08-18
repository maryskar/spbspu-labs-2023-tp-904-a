#include "commands.h"
#include <istream>
#include <exception>
#include "helpFunctions.h"
#include "../common/IofGuard.h"
namespace timofeev
{
  void doAreaCommands(std::istream &in, const std::vector< Polygon >& res)
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
      doEven(res);
    }
    else if (secPart == "ODD")
    {
      doOdd(res);
    }
    else if (secPart == "MEAN")
    {
      doMean(res);
    }
    else
    {
      throw std::logic_error("Error");
    }
  }

  void doMaxCommands(std::istream &in, const std::vector< Polygon >& res)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return;
    }
    std::string secPart;
    in >> secPart;
    if (secPart == "AREA")
    {
      doMaxArea(res);
    }
    else if (secPart == "VERTEXES")
    {
      doMaxV(res);
    }
    else
    {
      throw std::logic_error("Error");
    }
  }

  void doMinCommands(std::istream &in, const std::vector< Polygon >& res)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return;
    }
    std::string secPart;
    in >> secPart;
    if (secPart == "AREA")
    {
      doMinArea(res);
    }
    else if (secPart == "VERTEXES")
    {
      doMinV(res);
    }
    else
    {
      throw std::logic_error("Error");
    }
  }

  void doCountCommands(std::istream &in, const std::vector< Polygon >& res)
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
      doСountEven(res);
    }
    else if (secPart == "ODD")
    {
      doCountOdd(res);
    }
    else
    {
      throw std::logic_error("Error");
    }
  }

}
