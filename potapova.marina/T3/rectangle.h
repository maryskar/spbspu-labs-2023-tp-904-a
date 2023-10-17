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
    public:
      Rectangle() noexcept;
      void expandBounds(const Point& point) noexcept;
      void expandBounds(const Polygon& polygon) noexcept;
      void expandBounds(const std::deque< Polygon >& polygons) noexcept;
      bool isPointInFrame(const Point& point) noexcept;
      bool isPolygonInFrame(const Polygon& polygon) noexcept;
  };

  class RectExpandIterator
  {
    public:
      RectExpandIterator(Rectangle& rect) noexcept;
      RectExpandIterator& operator++() noexcept;
      RectExpandIterator& operator*() noexcept;

      template< typename AddedT, typename = std::enable_if_t< !std::is_same< AddedT, RectExpandIterator>::value > >
      RectExpandIterator& operator=(const AddedT& added) noexcept
      {
        rect_ptr_->expandBounds(added);
        return *this;
      }

    private:
      Rectangle* rect_ptr_;
  };
}

#endif
