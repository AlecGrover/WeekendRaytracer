//
// Created by alecg on 7/15/2022.
//

#include "Sphere.h"
#include "QuadraticHelper.h"
#include <cmath>

bool Sphere::b_ray_hit(const Ray& r, double t_min, double t_max, hit& hit_out) const {

    auto origin_to_center= (r.get_origin() - location);
    auto c= origin_to_center.length_squared() - radius * radius;

    auto a= r.get_direction().length_squared();
    auto half_b= dot(r.get_direction(), origin_to_center);

    if (!get_valid_t_simplified(a, half_b, c, t_min, t_max, hit_out.t)) return false;
    hit_out.hit_location= r.at(hit_out.t);
    hit_out.normal= get_normal_at_point(hit_out.hit_location);
    auto outward_n= (hit_out.hit_location - location) / radius;
    hit_out.determine_face(r, outward_n);

    return true;
}

Color Sphere::color_from_ray(Ray r) {

    auto origin_to_center= (r.get_origin() - location);
    auto c= origin_to_center.length_squared() - radius * radius;

    auto a= r.get_direction().length_squared();
    auto half_b= dot(r.get_direction(), origin_to_center);

    double t= get_closest_t(a, half_b, c);

    Vector3 normal= get_normal_at_point(r.at(t));

    double parallelism= 1.0 - cross(normal, r.get_direction()).length();

    return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    // return Color(1, 0.41, 0.12) * (parallelism + 1) * 0.5;
}

Color Sphere::color_from_hit(const hit& h) {
    return 0.5 * Color(h.normal.x() + 1, h.normal.y() + 1, h.normal.z() + 1);
}

Sphere::Sphere(Point3 location, double radius) : Shape(location), radius(radius) { }
