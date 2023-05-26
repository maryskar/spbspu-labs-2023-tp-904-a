#ifndef READPOLYGONS_H
#define READPOLYGONS_H

#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <limits>
#include "data_struct.h"
#include "io.h"

namespace tarasenko
{
  std::ostream& operator<<(std::ostream& out, const Polygon& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    for (auto i: src.points)
    {
      out << '(' << i.x << ";" << i.y << ')' << " ";
    }
    return out;
  }

  std::istream& operator>>(std::istream& in, Polygon& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Polygon input;
    {
      using sep = DelimiterIO;

      size_t n;
      in >> n;
      for (size_t i = 0; i < n; i++)
      {
        Point p;
        in >> sep{'('} >> p.x >> sep{';'} >> p.y >> sep{')'};
        input.points.push_back(p);
      }
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::vector< Polygon > readPolygons(std::istream& in)
  {
    std::vector< Polygon > polygons;
    while (in)
    {
      using in_iter = std::istream_iterator< Polygon >;
      while (!in.eof())
      {
        std::copy(in_iter(in), in_iter(), std::back_inserter(polygons));
        if (!in)
        {
          in.clear();
          std::string trash = "";
          std::getline(in, trash);
        }
      }
    }
    return polygons;
  }
}
#endif
