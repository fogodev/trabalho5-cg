cmake_minimum_required(VERSION 3.12)
project(Trab5)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp globals.h Point2D.h Polygonal.h Triangle.h Edge.h Delaunay.h Point3D.h ArcBall.cpp ArcBall.h Bezier.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

