#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <limits>
#include <deque>
#include "dataStruct.h"

namespace potapova
{
  class Rectangle
  {
    private:
      int max_x;
      int min_x;
      int max_y;
      int min_y;

      void expandBounds(const Point& point) noexcept;
      void expandBounds(const Polygon& polygon) noexcept;
    public:
      Rectangle():
        max_x(std::numeric_limits< int >::max()),
        min_x(std::numeric_limits< int >::lowest()),
        max_y(std::numeric_limits< int >::max()),
        min_y(std::numeric_limits< int >::lowest())
      {

      }

      static Rectangle getRectWichCanInclude(const std::deque< Polygon >& polygons);
      void expandBounds(const std::deque< Polygon >& polygons) noexcept;
      bool isInFrame(const Point& point);
      bool isPolygonInFrame(const Polygon& polygon);
  };

  class RectExpandIterator
  {
    public:
      RectExpandIterator(Rectangle& rect):
        rect_(rect)
      {

      }

      RectExpandIterator& operator++() noexcept
      {
        return *this;
      }

      RectExpandIterator& operator*() noexcept
      {
        return *this;
      }

      template< typename AddedT >
      RectExpandIterator& operator=(const AddedT& added) noexcept
      {
        rect_.expandBounds(added);
        return *this;
      }

    private:
      Rectangle& rect_;
  };
}

#endif
