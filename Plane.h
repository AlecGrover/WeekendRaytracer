//
// Created by alecg on 8/2/2022.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H


#include "Shape.h"

class Plane : public Shape {

public:
    Plane(double height, std::shared_ptr<Material> material);

    bool b_ray_hit(const Ray& r, double t_min, double t_max, hit& hit_out) const override;
    Color color_from_ray(Ray r) override;

    Color color_from_hit(const hit &h) override;

public:
    double height;
};


#endif //RAYTRACER_PLANE_H
