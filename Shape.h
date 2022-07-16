//
// Created by alecg on 7/15/2022.
//

#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H


#include "Vector3.h"
#include "Ray.h"

class Shape {
public:
    Point3 location;

public:
    Shape(Point3 location);

    virtual bool b_ray_hit(Ray r);
    virtual Color color_from_ray(Ray r);
    virtual Vector3 get_normal_at_point(Point3 point);
};

#endif //RAYTRACER_SHAPE_H
