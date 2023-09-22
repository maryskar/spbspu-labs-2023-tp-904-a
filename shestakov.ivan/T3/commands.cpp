#include "commands.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <functional>
#include "auxiliary_commands.h"

namespace shestakov
{
  //
  void areaEven(const std::vector<Polygon>& polygons, std::ostream &out)
  {
    size_t size_of_even = 0;
    double even_area = 0.0;
    size_of_even = std::count_if(polygons.begin(), polygons.end(), isEven);
    std::vector< double > ar_of_even_polygons(size_of_even);
    std::vector< Polygon > even_polygons(size_of_even);
    std::copy_if(polygons.begin(), polygons.end(), even_polygons.begin(), isEven);
    std::transform(even_polygons.begin(), even_polygons.end(), ar_of_even_polygons.begin(), getArea);
    even_area = std::accumulate(ar_of_even_polygons.begin(), ar_of_even_polygons.end(), 0.0);
    printFix(even_area, out);
  }
  void areaOdd(const std::vector<Polygon>& polygons, std::ostream &out)
  {
    size_t size_of_odd = 0;
    double odd_area = 0.0;
    size_of_odd = std::count_if(polygons.begin(), polygons.end(), isOdd);
    std::vector< double > ar_of_odd_polygons(size_of_odd);
    std::vector< Polygon > odd_polygons(size_of_odd);
    std::copy_if(polygons.begin(), polygons.end(), odd_polygons.begin(), isOdd);
    std::transform(odd_polygons.begin(), odd_polygons.end(), ar_of_odd_polygons.begin(), getArea);
    odd_area = std::accumulate(ar_of_odd_polygons.begin(), ar_of_odd_polygons.end(), 0.0);
    printFix(odd_area, out);
  }
  void areaMean(const std::vector<Polygon>& polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("");
    }
    double area_mean = 0.0;
    double area_sum = 0.0;
    std::vector< double > ar_of_polygons(polygons.size());
    std::transform(polygons.begin(), polygons.end(), ar_of_polygons.begin(), getArea);
    area_sum = std::accumulate(ar_of_polygons.begin(), ar_of_polygons.end(), 0.0);
    area_mean = area_sum / double(polygons.size());
    printFix(area_mean, out);
  }
  void maxArea(const std::vector<Polygon>& polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("");
    }
    std::vector< double > ar_of_polygons(polygons.size());
    std::transform(polygons.begin(), polygons.end(), ar_of_polygons.begin(), getArea);
    std::sort(ar_of_polygons.begin(), ar_of_polygons.end());
    printFix(ar_of_polygons.back(), out);
  }
  void minArea(const std::vector<Polygon>& polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("");
    }
    std::vector< double > ar_of_polygons(polygons.size());
    std::transform(polygons.begin(), polygons.end(), ar_of_polygons.begin(), getArea);
    std::sort(ar_of_polygons.begin(), ar_of_polygons.end());
    printFix(ar_of_polygons.front(), out);
  }
  void maxVertexes(const std::vector<Polygon>& polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("");
    }
    std::vector< size_t > count_vert(polygons.size());
    std::transform(polygons.begin(), polygons.end(), count_vert.begin(), countVertexes);
    std::sort(count_vert.begin(), count_vert.end());
    out << count_vert.back() << '\n';
  }
  void minVertexes(const std::vector<Polygon>& polygons, std::ostream &out)
  {
    std::vector< size_t > count_vert(polygons.size());
    std::transform(polygons.begin(), polygons.end(), count_vert.begin(), countVertexes);
    std::sort(count_vert.begin(), count_vert.end());
    out << count_vert.front() << '\n';
  }
  void countEven(const std::vector<Polygon>& polygons, std::ostream &out)
  {
    size_t size_even = 0;
    size_even = std::count_if(polygons.begin(), polygons.end(), isEven);
    out << size_even << '\n';
  }
  void countOdd(const std::vector<Polygon>& polygons, std::ostream &out)
  {
    size_t size_odd = 0;
    size_odd = std::count_if(polygons.begin(), polygons.end(), isOdd);
    out << size_odd << '\n';
  }
  void countVert(const std::vector<Polygon>& polygons, size_t num, std::ostream &out)
  {
    if (num < 3)
    {
      printError(out);
    }
    else
    {
      size_t num_of_vert = 0;
      std::vector< size_t > vert(polygons.size(), num);
      std::vector< bool > equal(polygons.size());
      std::transform(polygons.begin(), polygons.end(), vert.begin(), equal.begin(), equalVert);
      num_of_vert = std::accumulate(equal.begin(), equal.end(), 0);
      out << num_of_vert << '\n';
    }
  }
  void areaVert(const std::vector<Polygon>& polygons, size_t num, std::ostream &out)
  {
    if(num < 3)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    else
    {
      std::vector<Polygon> vert_polygons;
      double sum_areas = 0.0;
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(vert_polygons),
                   std::bind(equalVert, std::placeholders::_1, num));
      std::vector<double> areas(vert_polygons.size());
      std::transform(vert_polygons.begin(), vert_polygons.end(), areas.begin(), getArea);
      sum_areas = std::accumulate(areas.begin(), areas.end(), 0.0);
      printFix(sum_areas, out);
    }
  }
  void rmecho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    Polygon input;
    if (in >> input)
    {
      std::string remaining;
      std::getline(in, remaining);
      if (!remaining.empty())
      {
        throw std::logic_error("");
      }
      auto new_end = std::unique(polygons.begin(), polygons.end(), std::bind(compThreePolygons, _1, _2, input));
      size_t count_polygons = std::distance(new_end, polygons.end());
      polygons.erase(new_end, polygons.end());
      out << std::fixed << std::setprecision(1);
      out << count_polygons << '\n';
    }
    else
    {
      throw std::logic_error("");
    }
  }
  void echo(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    Polygon input;
    in >> input;
    if (!in)
    {
      in.clear();
      throw std::logic_error("wrong input...");
    }
    char c = '0';
    in.get(c);
    if (input.points.size() > 2 && c == '\n')
    {
      std::vector<Polygon> polygons_1;
      size_t i = 0;
      size_t count_echo = 0;
      while (i < polygons.size())
      {
        if (compTwoPolygons(polygons[i], input))
        {
          polygons_1.push_back(polygons[i]);
          ++count_echo;
        }
        polygons_1.push_back(polygons[i]);
        ++i;
      }
      polygons.assign(polygons_1.begin(), polygons_1.end());
      out << count_echo << '\n';
    }
    else if (c != '\n')
    {
      throw std::logic_error("");
    }
  }
}
