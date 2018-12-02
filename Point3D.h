#ifndef TRAB4_POINT3D_H
#define TRAB4_POINT3D_H

#include <cmath>
#include <limits>

struct Point3D {

  double x, y, z;

  Point3D() = default;

  Point3D(double x, double y, double z) noexcept :
      x(x),
      y(y),
      z(z) {}

  Point3D change_coordinates(double dim_x, double dim_y, double dim_z) {
    return {(2. * x) / dim_x - 1., -(2. * y) / dim_y + 1., (2. * z) / dim_z - 1.};
  }

  Point3D& operator+=(const Point3D& other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
  }

  Point3D& operator-=(const Point3D& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
  }

  Point3D& operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
  }

  Point3D& operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;
  }

  Point3D operator+(const Point3D& other) const {
    return {x + other.x, y + other.y, z + other.z};
  }

  Point3D operator-(const Point3D& other) const {
    return {x - other.x, y - other.y, z - other.z};
  }

  Point3D operator*(double scalar) const {
    return {x * scalar, y * scalar, z * scalar};
  }

  Point3D operator/(double scalar) const {
    return {x / scalar, y / scalar, z / scalar};
  }

  bool operator!=(const Point3D& other) const {
    return !(*this == other);
  }

  bool operator==(const Point3D& other) const {
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
                )
            &&
                (
                    std::abs(z - other.z)
                        >= std::numeric_limits<double>::epsilon() * std::abs(z + other.z) * 2 ||
                        std::abs(z - other.z) < std::numeric_limits<double>::min()
                );
  }

  double dot(const Point3D& other) const {
    return x * other.x + y * other.y + z * other.z;
  }

  double norm_squared() const {
    return x * x + y * y + z * z;
  }

  double norm() const {
    return std::sqrt(norm_squared());
  }

  double distance_squared(const Point3D& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    double dz = z - other.z;

    return dx * dx + dy * dy + dz * dz;
  }

  double distance(const Point3D& other) const {
    return std::sqrt(distance_squared(std::forward<const Point3D&>(other)));
  }

  Point3D cross(const Point3D& other) const {
    return {y * other.z - z * other.y, -(x * other.z - z * other.x), x * other.y - y * other.x};
  }

  double theta(const Point3D& other) const {
    return std::acos(dot(std::forward<const Point3D&>(other)) / (norm() * other.norm()));
  }

};

#endif //TRAB4_POINT3D_H
