#ifndef TRAB4_EDGE_H
#define TRAB4_EDGE_H

#include "Point2D.h"

class Edge {
 public:
  Edge(const Point2D<double>& point1, const Point2D<double>& point2) : point1(point1), point2(point2) {}
  Edge(const Edge& other) : point1(other.point1), point2(other.point2) {}

  bool operator==(const Edge& other) const {
    return (point1 == other.point1 && point2 == other.point2) ||
        (point1 == other.point2 && point2 == other.point1);
  }

  void invalidate() {
    bad = true;
  }

  bool is_bad() const {
    return bad;
  }

  Point2D<double> get_point1() const {
    return point1;
  }

  Point2D<double> get_point2() const {
    return point2;
  }

 private:
  Point2D<double> point1;
  Point2D<double> point2;
  bool bad = false;
};

#endif //TRAB4_EDGE_H
