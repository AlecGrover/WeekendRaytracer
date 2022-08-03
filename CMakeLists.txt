cmake_minimum_required(VERSION 3.20)
project(Raytracer)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenMP)
add_executable(Raytracer main.cpp Vector3.cpp Vector3.h Color.cpp Color.h Ray.cpp Ray.h Shape.h Sphere.cpp Sphere.h Shape.cpp QuadraticHelper.h util.h Camera.cpp Camera.h Material.cpp Material.h Lambertian.cpp Lambertian.h Metal.cpp Metal.h Dielectric.cpp Dielectric.h Quaternion.cpp Quaternion.h Rotation.cpp Rotation.h Plane.cpp Plane.h)
if(OpenMP_CXX_FOUND)
    target_link_libraries(Raytracer PRIVATE OpenMP::OpenMP_CXX)
endif()