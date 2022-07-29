//
// Created by alecg on 7/15/2022.
//

#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H


#include "Vector3.h"
#include "Ray.h"
#include "Material.h"

class Material;

struct hit {
    Point3 hit_location;
    Vector3 normal;
    double t;
    bool front_face;
    std::shared_ptr<Material> material;

    inline void determine_face(const Ray& r, const Vector3& outward_normal) {
        front_face= dot(r.get_direction(), outward_normal) < 0;
        normal= front_face ? outward_normal : -outward_normal;
    }
};

class Shape {
public:
    Point3 location;
    std::shared_ptr<Material> material;

public:
    explicit Shape(Point3 location, std::shared_ptr<Material> material);

    virtual bool b_ray_hit(const Ray& r, double t_min, double t_max, hit& hit_out) const = 0;
    virtual Color color_from_hit(const hit &h) = 0;
    virtual Color color_from_ray(Ray r);
    virtual Vector3 get_normal_at_point(Point3 point) const;
};

#endif //RAYTRACER_SHAPE_H
