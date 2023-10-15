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
    if (is_number(secPart))
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

  void doRSCommand(std::istream&, const std::vector< Polygon > &res)
  {
    size_t count = 0;
    for (const Polygon& polygon : res)
    {
      for (size_t i = 0; i < polygon.points.size(); i++)
      {
        const Point& p1 = polygon.points[i];
        const Point& p2 = polygon.points[(i + 1) % polygon.points.size()];
        const Point& p3 = polygon.points[(i + 2) % polygon.points.size()];

        int vector1_x = p2.x - p1.x;
        int vector1_y = p2.y - p1.y;
        int vector2_x = p3.x - p2.x;
        int vector2_y = p3.y - p2.y;

        if (vector1_x * vector2_x + vector1_y * vector2_y == 0)
        {
          count++;
          break;
        }
      }
    }
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
