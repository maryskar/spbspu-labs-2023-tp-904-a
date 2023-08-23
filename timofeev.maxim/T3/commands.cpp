#include "commands.h"
#include <istream>
#include <exception>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "helpFunctions.h"
#include "../common/IofGuard.h"
namespace timofeev
{
  using outV =  std::ostream_iterator< size_t >;
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
      size_t tmp = std::stoull(secPart);
      if (tmp < 3)
      {
        throw std::logic_error("Error");
      }
      else
      {
        doAreaV(res, tmp);  // Дописать
      }
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
      size_t tmp = std::stoull(secPart);
      if (tmp < 3)
      {
        throw std::logic_error("Error");
      }
      else
      {
        doCountV(res, tmp);
      }
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

  void doRSCommand(std::istream &in, const std::vector< Polygon >& res)
  {
    size_t val = std::count_if(res.begin(), res.end(), isRectangle);
    std::vector< size_t > vec;
    vec.push_back(val);
    std::copy(vec.begin(), vec.end(), outV(std::cout, "\n"));
  }

  void doRectsCommand(std::istream &in, const std::vector< Polygon >& res)
  {
    size_t val = std::count_if(res.begin(), res.end(), isAngle);
    std::vector< size_t > vec;
    vec.push_back(val);
    std::copy(vec.begin(), vec.end(), outV(std::cout, "\n"));
  }

}
