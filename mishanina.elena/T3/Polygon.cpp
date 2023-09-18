#include "Polygon.h"
namespace mishanina{

//  std::istream &operator>>(std::istream &in, Point &point)
//  {
//    std::istream::sentry sentry(in);
//    if (!sentry) {
//      return in;
//    }
//    return in >> DelimiterIO{ '(' } >> point.x >> DelimiterIO{ ';' } >> point.y >> DelimiterIO{ ')' };
//  }

//  std::istream &operator>>(std::istream &in, Polygon &data){
//    std::istream::sentry sentry(in);
//    if (!sentry) {
//      return in;
//    }
//    std::size_t count = 0;
//    in >> count;
//    if (count < 3) {
//      in.setstate(std::ios::failbit);
//    }
//    Polygon pol;
//    std::copy_n(std::istream_iterator<Point>(in), count, std::back_inserter(pol.points));
//    if (in) {
//      pol = data;
//    }
//    return in;
//  }

  std::ostream &operator<<(std::ostream &out, const Point &data){

  }
  std::ostream &operator<<(std::ostream &out, const Polygon &data){

  }

}
