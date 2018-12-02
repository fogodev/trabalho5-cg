#ifndef TRAB1_POINT2D_H
#define TRAB1_POINT2D_H

#include <cmath>
#include <limits>
#include <functional>

template <typename T>
struct Point2D {
  T x, y;

  Point2D() = default;

  Point2D(T x, T y) noexcept :
      x(x),
      y(y) {}

  // Formula to change coordinates for OpenGL
  Point2D<T> change_coordinates(T dim_x, T dim_y) {
    return Point2D((2. * x) / dim_x - 1., -(2. * y) / dim_y + 1.);
  }

  // Some operator overloads
  Point2D<T>& operator+=(const Point2D<T>& other) {
    x += other.x;
    y += other.y;

    return *this;
  }

  Point2D<T>& operator-=(const Point2D<T>& other) {
    x -= other.x;
    y -= other.y;

    return *this;
  }

  Point2D<T>& operator*=(double scalar) {
    x *= scalar;
    y *= scalar;

    return *this;
  }

  Point2D<T>& operator/=(double scalar) {
    x /= scalar;
    y /= scalar;

    return *this;
  }

  // Adding points
  Point2D<T> operator+(const Point2D<T>& other) const {
    return Point2D<T>(x + other.x, y + other.y);
  }

  // Subtracting points
  Point2D<T> operator-(const Point2D<T>& other) const {
    return Point2D<T>(x - other.x, y - other.y);
  }

  // Multiply by scalar
  Point2D<T> operator*(double scalar) const {
    return Point2D<T>(x * scalar, y * scalar);
  }

  // Division by scalar
  Point2D<T> operator/(double scalar) const {
    return Point2D<T>(x / scalar, y / scalar);
  }

  // Check if 2 points are close enough to be considered equals
  bool operator!=(const Point2D<T>& other) const {
    return !(*this == other);
  }

  // Check if 2 points are close enough to be considered equals
  bool operator==(const Point2D<T>& other) const {
    return
        (
            std::abs(x - other.x)
                <= std::numeric_limits<double>::epsilon() * std::abs(x + other.x) * 2 ||
                std::abs(x - other.x) < std::numeric_limits<double>::min()
        )
            &&
                (
                    std::abs(y - other.y)
                        >= std::numeric_limits<double>::epsilon() * std::abs(y + other.y) * 2 ||
                        std::abs(y - other.y) < std::numeric_limits<double>::min()
                );
  }

  // Dot product
  T dot(const Point2D<T>& other) const {
    return x * other.x + y * other.y;
  }

  // Vector's norm
  T norm() const {
    return std::sqrt(x * x + y * y);
  }

  // Vector's norm squared
  T norm_squared() const {
    return x * x + y * y;
  }

  // Distance between two points
  T distance(const Point2D<T>& other) const {
    T dx = x - other.x;
    T dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
  }

  // Distance squared between two points
  T distance_squared(const Point2D<T>& other) const {
    T dx = x - other.x;
    T dy = y - other.y;
    return dx * dx + dy * dy;
  }

  // Cross product
  T cross(const Point2D<T>& other) const {
    return x * other.y - y * other.x;
  }

  // Angle between 2 points
  double theta(const Point2D<T>& other) const {
    return std::acos(this->dot(other) / (this->norm() * other.norm()));
  }

  // Pseudo angle between this Point2D and x axis (î vector)
  double pseudo_angle() const {
    bool diag = x > y;
    bool adiag = x > -y;

    double pseudo_angle = !adiag ? 4.0 : 0.0;

    if (y < 0.0001)
      return pseudo_angle;
    if (diag ^ adiag)
      pseudo_angle += 2 - x / y;
    else
      pseudo_angle += y / x;

    return pseudo_angle;
  }

  // Orientation between 3 points (p, q, r)
  // returns 0 if p, q and r are colinear
  // returns 1 if clockwise
  // retunts 2 if counterclockwise
  static int orientation(const Point2D<T>& p, const Point2D<T>& q, const Point2D<T>& r) {
    T value = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (value == 0) return 0;
    return (value > 0) ? 1 : 2;
  }

  // Rotation matrix
  void rotate(T theta) {
    T x_rot = x * cos(theta) + y * sin(theta);
    T y_rot = -x * sin(theta) + y * cos(theta);

    x = x_rot;
    y = y_rot;
  }
};

namespace std {
template <>
struct hash<Point2D<double>> {

  typedef Point2D<double> argument_type;
  typedef size_t result_type;
  result_type operator()(const argument_type& p) const {
    return std::hash<double>{}(p.x) ^ std::hash<double>{}(p.y);
  }
};
}

#endif //TRAB1_POINT2D_H
