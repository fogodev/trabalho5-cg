#ifndef TRAB1_GLOBALS_H
#define TRAB1_GLOBALS_H

#include <vector>

#include "Point2D.h"
#include "Point3D.h"
#include "Polygonal.h"
#include "Triangle.h"
#include "ArcBall.h"
#include "Bezier.h"

enum class Mode {
  idle,
  lines,
  bezier,
  drawing_polygon,
  checking_if_inside_polygon,
  marking_points,
  convex_hull,
  triangulate
};

const int width = 800;
const int height = 800;

Mode mode = Mode::idle;

const Point2D<double> outsider =
    Point2D<double>(double(width + width), double(height + height)).change_coordinates(width, height);
Polygonal<double> polygon;
std::vector<Point3D> points = {
    Point3D(700, 700, 700).change_coordinates(width, height, 800),
    Point3D(600, 500, 500).change_coordinates(width, height, 800),
    Point3D(400, 300, 450).change_coordinates(width, height, 800),
    Point3D(450, 400, 200).change_coordinates(width, height, 800),
    Point3D(100, 300, 400).change_coordinates(width, height, 800),
    Point3D(-100, 100, 200).change_coordinates(width, height, 800),
    Point3D(0, 300, 100).change_coordinates(width, height, 800),
    Point3D(-200, -300, 0).change_coordinates(width, height, 800),
    Point3D(100, -500, -200).change_coordinates(width, height, 800),
    Point3D(-400, 300, -400).change_coordinates(width, height, 800),
};
std::vector<Triangle> triangles;
Bezier3D bezier{points, 30};

ArcBall arcball;

#endif //TRAB1_GLOBALS_H
