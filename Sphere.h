//
// Created by alecg on 7/15/2022.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "Shape.h"

class Sphere : public Shape {

public:
    double radius;

public:
    Sphere(Point3 location, double radius);

    bool b_ray_hit(Ray r) override;
    Color color_from_ray(Ray r) override;
};


#endif //RAYTRACER_SPHERE_H
