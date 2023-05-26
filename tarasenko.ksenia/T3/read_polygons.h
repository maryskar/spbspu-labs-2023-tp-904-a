#ifndef READPOLYGONS_H
#define READPOLYGONS_H

#include <vector>
#include <string>
#include <fstream>
#include <exception>
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
      out << i.x << ";" << i.y << " ";
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

  std::vector< Polygon > readPolygons(const std::string& filename)
  {
    std::vector< Polygon > polygons;
    std::ifstream input(filename);
    if (!input.is_open())
    {
      throw std::invalid_argument("File not found");
    }
    while (input)
    {
      Polygon polygon;
      if (input >> polygon)
      {
        polygons.push_back(polygon);
        input.clear();
      }
      else
      {
        input.clear();
        std::string trash = "";
        std::getline(input, trash);
      }
    }
    return polygons;
  }
}
#endif
