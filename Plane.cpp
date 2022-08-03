//
// Created by alecg on 8/2/2022.
//

#include "Plane.h"

Plane::Plane(double height, std::shared_ptr<Material> material) : Shape(Vector3(0, height, 0), material), height(height){

}

bool Plane::b_ray_hit(const Ray &r, double t_min, double t_max, hit &hit_out) const {
    auto normal= Vector3(0, 1, 0);
    if (dot(r.get_direction(), normal) < 0.00001) return false;
    auto t= dot((r.get_origin() - Point3(0, height, 0)), normal) / dot(r.get_direction(), normal);
    if (t < t_min || t > t_max) return false;
    hit_out.hit_location= r.at(t);
    hit_out.normal= normal;
    hit_out.material= material;
    hit_out.front_face= r.get_origin().y() > height;

    return true;
}

Color Plane::color_from_ray(Ray r) {
    return Shape::color_from_ray(r);
}

Color Plane::color_from_hit(const hit &h) {
    return 0.5 * Color(h.normal.x() + 1, h.normal.y() + 1, h.normal.z() + 1);
}
