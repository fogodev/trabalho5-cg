#ifndef TRAB4_DELAUNAY_H
#define TRAB4_DELAUNAY_H

#include <vector>
#include <algorithm>
#include <numeric>

#include "Point2D.h"
#include "Edge.h"
#include "Triangle.h"

class Delaunay {
 public:
  static const std::vector<Triangle> triangulate(const std::vector<Point2D<double>>& points) {
    auto super = super_triangle(points);

    std::vector<Triangle> triangles;
    triangles.push_back(super);

    for (auto point : points) {
      auto polygon = polygon_from_triangles(triangles, point);
      clean_bad_triangles(triangles);
      remove_duplicated_points(polygon);

      for (const auto& edge: polygon) {
        triangles.emplace_back(edge.get_point1(), edge.get_point2(), point);
      }
    }

    clean_super_triangle(triangles, super);
    return std::move(triangles);
  }

 private:

  static Triangle super_triangle(const std::vector<Point2D<double>>& points) {
    double smallest_x = points[0].x;
    double smallest_y = points[0].y;
    double biggest_x = smallest_x;
    double biggest_y = smallest_y;

    for (const auto& point : points) {
      if (point.x < smallest_x) smallest_x = point.x;
      if (point.y < smallest_y) smallest_y = point.y;
      if (point.x > biggest_x) biggest_x = point.x;
      if (point.y > biggest_y) biggest_y = point.y;
    }

    const double dx = biggest_x - smallest_x;
    const double dy = biggest_y - smallest_y;
    const double max = dx > dy ? dx : dy;
    const double mid_x = (smallest_x + biggest_x) * 0.5;
    const double mid_y = (smallest_y + biggest_y) * 0.5;

    return {
        {mid_x - 20.0 * max, mid_y - max},
        {mid_x, mid_y + 20.0 * max},
        {mid_x + 20.0 * max, mid_y - max}
    };
  }

  static const std::vector<Edge> polygon_from_triangles(std::vector<Triangle>& triangles,
                                                        Point2D<double> point) {
    std::vector<Edge> polygon;

    for (auto& triangle : triangles) {
      if (triangle.contains_in_circle(point)) {
        triangle.invalidate();
        polygon.push_back(triangle.get_edge1());
        polygon.push_back(triangle.get_edge2());
        polygon.push_back(triangle.get_edge3());
      }
    }

    return polygon;
  }

  static void remove_duplicated_points(std::vector<Edge>& polygon) {
    for (auto iter = polygon.begin(); iter != polygon.end(); ++iter) {
      for (auto iter2 = iter + 1; iter2 != polygon.end(); ++iter2) {
        if (*iter == *iter2) {
          iter->invalidate();
          iter2->invalidate();
        }
      }
    }

    polygon.erase(
        std::remove_if(polygon.begin(), polygon.end(), [](const Edge& e) { return e.is_bad(); }),
        polygon.end()
    );
  }

  static void clean_bad_triangles(std::vector<Triangle>& triangles) {
    triangles.erase(
        std::remove_if(triangles.begin(),
                       triangles.end(),
                       [](const Triangle& t) { return t.is_bad(); }),
        triangles.end()
    );
  }

  static void clean_super_triangle(std::vector<Triangle>& triangles, const Triangle& super) {
    triangles.erase(
        std::remove_if(triangles.begin(),
                       triangles.end(),
                       [&super](const Triangle& t) {
                         return t.contains_point(super.get_point1())
                             || t.contains_point(super.get_point2())
                             || t.contains_point(super.get_point3());
                       }),
        triangles.end()
    );
  }
};

#endif //TRAB4_DELAUNAY_H
