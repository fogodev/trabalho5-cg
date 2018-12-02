#include <GL/gl.h>     // The GL Header File
#include <GL/freeglut.h>   // The GL Utility Toolkit (Glut) Header

#include <cmath>
#include <vector>

#include "globals.h"
#include "Point2D.h"
#include "Delaunay.h"

// Respond to mouse button presses.
GLint viewport[4];
double ux, uy;

void mouse_points(int button, int state, int x, int y) {
  if (state == GLUT_DOWN) {
    glGetIntegerv(GL_VIEWPORT, viewport);
    ux = (2.0 * (x - viewport[0])) / viewport[2] - 1.0;
    uy = 1.0 - (2.0 * (y - viewport[1])) / viewport[3];
  } else if (state == GLUT_UP) {
    double vx = (2.0 * (x - viewport[0])) / viewport[2] - 1.0;
    double vy = 1.0 - (2.0 * (y - viewport[1])) / viewport[3];

    arcball.click(ux, uy, vx, vy);

    glutPostRedisplay();
  }
}

void motion_cb(int x, int y) {
  double vx = (2.0 * (x - viewport[0])) / viewport[2] - 1.0;
  double vy = 1.0 - (2.0 * (y - viewport[1])) / viewport[3];
  arcball.click(ux, uy, vx, vy);
  ux = vx;
  uy = vy;

  glutPostRedisplay();
}

void keyboard_cb(unsigned char key, int X, int Y) {
  switch (key) {
    case 27:             // ESCAPE key
//      points = std::move(std::vector<Point2D<double>>{}); // Cleaning points
//      triangles = std::move(std::vector<Triangle>{});
      mode = Mode::idle; // Reset mode
      glutPostRedisplay();
      break;

    case 'l':
      if (mode != Mode::lines) {
        mode = Mode::lines;

      }
      glutPostRedisplay();
      break;

    case 'b':
      if (mode != Mode::bezier) {
        mode = Mode::bezier;
      }
      glutPostRedisplay();
  }
}

void reshape_cb(GLint width, GLint height) {
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLdouble) width / height, 0.1, 8.0);
  gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0);

  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

void draw_points() {
  glBegin(GL_POINTS);
  glColor3f(0, 1.0, 0);
  glPointSize(100.0);

  for (const auto& point : points) {
    glVertex3d(point.x, point.y, point.z);
  }
  glEnd();
}

void draw_lines() {
  glBegin(GL_LINE_STRIP);
  glColor3f(1.0, 0, 0);
  glPointSize(100.0);

  for (const auto& point : points) {
    glVertex3d(point.x, point.y, point.z);
  }
  glEnd();
}

void draw_bezier() {
  glBegin(GL_LINE_STRIP);
  glColor3f(1.0, 1.0, 0);
  glPointSize(100.0);

  for (const auto& point : bezier.get_curve()) {
    glVertex3d(point.x, point.y, point.z);
  }
  glEnd();
}

void display_cb() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glMultMatrixd(arcball.get_rotation_matrix());

  {
    glColor3f(1, 1, 1);
    glutWireSphere(2.0, 8, 6);
  }

  switch (mode) {
    case Mode::idle:
      draw_points();
      break;

    case Mode::lines:
      draw_points();
      draw_lines();
      break;

    case Mode::bezier:
      draw_points();
      draw_lines();
      draw_bezier();
      break;

  }

  glutSwapBuffers();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
  glutCreateWindow("3D Bezier Curve");

  // Set up OpenGL lights
  GLfloat light0_ambient[] = {0.1f, 0.1f, 0.3f, 1.0f};
  GLfloat light0_diffuse[] = {0.6f, 0.6f, 1.0f, 1.0f};
  GLfloat light0_position[] = {1.0f, 1.0f, 1.0f, 0.0f};

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_AUTO_NORMAL);

  // anti-aliasing
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

  // openGL init
  glEnable(GL_DEPTH_TEST);

  // Register callbacks:
  glutDisplayFunc(display_cb);
  glutReshapeFunc(reshape_cb);
  glutKeyboardFunc(keyboard_cb);
  glutMouseFunc(mouse_points);
  glutMotionFunc(motion_cb);

  glutMainLoop();

  return EXIT_SUCCESS;
}
