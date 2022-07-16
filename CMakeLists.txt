cmake_minimum_required(VERSION 3.20)
project(Raytracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Raytracer main.cpp Vector3.cpp Vector3.h Color.cpp Color.h Ray.cpp Ray.h)
