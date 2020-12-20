cmake_minimum_required(VERSION 3.17)
project(Voronoi_3)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(BrutVoronoi run-brut-voronoi.cpp libs/brut-voronoi.h libs/germ.h deps/argparse.h libs/apply-colors-on-voronoi.h)
add_executable(SequentialVoronoi run-sequential-voronoi.cpp libs/brut-voronoi.h libs/germ.h deps/argparse.h libs/sequential-voronoi.h libs/apply-colors-on-voronoi.h)
add_executable(BrutVoronoiApproximation run-brut-voronoi-approximation.cpp libs/apply-colors-on-voronoi.h)

target_link_libraries(BrutVoronoi ${OpenCV_LIBS})
target_link_libraries(SequentialVoronoi ${OpenCV_LIBS})
target_link_libraries(BrutVoronoiApproximation ${OpenCV_LIBS})