cmake_minimum_required(VERSION 3.20)
project(Raytracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Raytracer main.cpp Vector3.cpp Vector3.h Color.cpp Color.h Ray.cpp Ray.h Shape.h Sphere.cpp Sphere.h Shape.cpp QuadraticHelper.h util.h Camera.cpp Camera.h Material.cpp Material.h Lambertian.cpp Lambertian.h Metal.cpp Metal.h)
