#include "commands.h"
#include <istream>
#include <iostream>
#include <iomanip>
#include "helpFunctions.h"
namespace timofeev
{
  void doAreaCommands(std::istream &in, const std::vector< Polygon > &res)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return;
    }
    std::string secPart;
    in >> secPart;
    try
    {
      size_t tmp = std::stoull(secPart);
      if (tmp < 3)
      {
        throw std::logic_error("Error");
      }
      else
      {
        doAreaV(res, tmp);
      }
    }
    catch (const std::invalid_argument &e)
    {
      if (secPart == "EVEN")
      {
        doEven(res);
      }
      else if (secPart == "ODD")
      {
        doOdd(res);
      }
      else if (secPart == "MEAN")
      {
        if (res.empty())
        {
          throw std::logic_error("Error");
        }
        doMean(res);
      }
      else
      {
        throw std::logic_error("Error");
      }
    }
  }

  void doMaxCommands(std::istream &in, const std::vector< Polygon > &res)
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

  void doMinCommands(std::istream &in, const std::vector< Polygon > &res)
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

  void doCountCommands(std::istream &in, const std::vector< Polygon > &res)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return;
    }
    std::string secPart;
    in >> secPart;
    try
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
    catch (const std::invalid_argument &e)
    {
      if (secPart == "EVEN")
      {
        doCountEven(res);
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
  void doRSCommand(std::istream&, const std::vector< Polygon > &res)
  {
    size_t count = 0;
    size_t indx = 0;
    size_t pindx = 0;
    recurRS(res, count, indx, pindx);
    std::cout << count << "\n";
  }

  void doRectsCommand(std::istream&, const std::vector< Polygon >& res)
  {
    size_t val = 0;
    for (const Polygon& p: res)
    {
      if (isAngle(p))
      {
        val++;
      }
    }
    std::cout << std::fixed << std::setprecision(1) << val << "\n";
  }
}
