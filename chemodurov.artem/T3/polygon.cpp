#include "polygon.hpp"
#include <sstream>
#include <iterator>
#include <IO-structs.hpp>

std::istream & chemodurov::operator>>(std::istream & in, Point & dest)
{
  if (!checkInSentry(in))
  {
    return in;
  }
  return in >> DelimiterIO{' '} >> DelimiterIO{'('} >> dest.x >> DelimiterIO{';'} >> dest.y >> DelimiterIO{')'};
}

std::istream & chemodurov::operator>>(std::istream & in, Polygon & dest)
{
  if (!checkInSentry(in))
  {
    return in;
  }
  size_t num_of_points = 0;
  in >> num_of_points;
  std::string line;
  std::getline(in, line);
  if (!in)
  {
    return in;
  }
  std::istringstream iss(line);
  std::copy(
    std::istream_iterator< Point >(iss),
    std::istream_iterator< Point >(),
    std::back_inserter(dest.data)
  );
  return in;
}
