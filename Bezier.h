#ifndef TRAB5_BEZIER_H
#define TRAB5_BEZIER_H

#include <vector>
#include "Point3D.h"

class Bezier3D {

  std::vector<Point3D> output;

 public:
  Bezier3D(const std::vector<Point3D>& input, size_t steps) {

    std::vector<Point3D> control_points;
    control_points.reserve(input.size());
    for (size_t index = 0; index < input.size() - 1; ++index) {
      control_points.push_back(input[index]);
      if (index != 0 && index % 2 == 0) {
        auto mid_point = input[index] + (input[index + 1] - input[index]) / 2;
        control_points.push_back(mid_point);
      }
    }
    control_points.push_back(input.back());

    double step_increment = 1.0 / steps;
    for (size_t begin_point_index = 0; begin_point_index + 3 < control_points.size(); begin_point_index += 3) {
      double current_step = 0;
      for (size_t _current_step = 0; _current_step <= steps; ++_current_step) {
        output.emplace_back(
            cubic(control_points[begin_point_index],
                  control_points[begin_point_index + 1],
                  control_points[begin_point_index + 2],
                  control_points[begin_point_index + 3],
                  current_step)
        );
        current_step += step_increment;
      }
    }

    output.push_back(input.back());
  }

  std::vector<Point3D>& get_curve() {
    return output;
  }

 private:
  Point3D quadratic(const Point3D& p0, const Point3D& p1, const Point3D& p2, double t) {
    double interpolation = (1.0 - t);
    double interpolation_squared = interpolation * interpolation;

    return {
        interpolation_squared * p0.x + interpolation * 2 * t * p1.x + t * t * p2.x,
        interpolation_squared * p0.y + interpolation * 2 * t * p1.y + t * t * p2.y,
        interpolation_squared * p0.z + interpolation * 2 * t * p1.z + t * t * p2.z,
    };
  }

  Point3D cubic(const Point3D& p0,
                const Point3D& p1,
                const Point3D& p2,
                const Point3D& p3,
                double t) {
    double interpolation = (1.0 - t);
    double interpolation_squared = interpolation * interpolation;
    double interpolation_cubed = interpolation_squared * interpolation;

    return {
        interpolation_cubed * p0.x + interpolation_squared * 3 * t * p1.x
            + interpolation * 3 * t * t * p2.x + t * t * t * p3.x,
        interpolation_cubed * p0.y + interpolation_squared * 3 * t * p1.y
            + interpolation * 3 * t * t * p2.y + t * t * t * p3.y,
        interpolation_cubed * p0.z + interpolation_squared * 3 * t * p1.z
            + interpolation * 3 * t * t * p2.z + t * t * t * p3.z,
    };
  }

};

#endif //TRAB5_BEZIER_H
