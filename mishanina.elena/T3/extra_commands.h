#ifndef EXTRA_COMMANDS_H
#define EXTRA_COMMANDS_H
#include "Polygon.h"
#include <numeric>
namespace mishanina{
  double getSide(const Point& p1, const Point& p2){
    return p1.x * p2.y - p1.y * p2.x;
  }
  double getArea(const Polygon& polygon){
    auto& points = polygon.points;

    //В этом примере мы использовали функцию std::transform,
    //чтобы вычислить произведения координат вершин и сохранить их в вектор products.
    //Затем мы использовали функцию std::accumulate,
    //чтобы найти сумму произведений,
    //и функцию std::abs, чтобы получить модуль этой суммы.
    //Наконец, мы разделили площадь на 2 и вернули ее из функции.


    // Создаем вектор сумм произведений координат вершин
    std::vector<int> products(points.size());
    std::transform(points.begin(), points.end(), points.begin(), products.begin(), getSide);

    // Считаем сумму произведений и находим модуль
    int sum = std::accumulate(products.begin(), products.end(), 0);
    int area = std::abs(sum);

    // Возвращаем площадь, разделенную на 2
    return area / 2.0;
  }
  template <class P>
  std::vector<Polygon> getPolygonsIf(const std::vector<Polygon>& polygons, P p)
  {
    std::vector<Polygon> polygonsIf;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(polygonsIf), p);
    return polygonsIf;
  }
  template <class P>
  double getAreaIf(const std::vector<Polygon>& polygons, P p) {
    std::vector<Polygon> polygonsIf = getPolygonsIf(polygons, p);
    std::vector<double> areas(polygonsIf.size());
    std::transform(polygonsIf.begin(), polygonsIf.end(), areas.begin(), getArea);
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
    return sum;
  }
  bool isEven(const Polygon& polygon) {
    return polygon.points.size() % 2 == 0;
  }

  bool isOdd(const Polygon& polygon) {
    return !isEven(polygon);
  }
}

#endif
