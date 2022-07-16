//
// Created by alecg on 7/15/2022.
//

#include "Sphere.h"
#include "QuadraticHelper.h"
#include <cmath>

bool Sphere::b_ray_hit(Ray r) {

    auto origin_to_center= (r.get_origin() - location);
    auto c= origin_to_center.length_squared() - radius * radius;

    auto a= r.get_direction().length_squared();
    auto b= 2.0 * dot(r.get_direction(), origin_to_center);

    auto radicand= b * b - 4 * a * c;

    return radicand >= 0;

}

Color Sphere::color_from_ray(Ray r) {

    auto origin_to_center= (r.get_origin() - location);
    auto c= origin_to_center.length_squared() - radius * radius;

    auto a= r.get_direction().length_squared();
    auto b= 2.0 * dot(r.get_direction(), origin_to_center);

    double t= get_closest_t(a, b, c);

    Vector3 normal= get_normal_at_point(r.at(t));

    double parallelism= 1.0 - cross(normal, r.get_direction()).length();

    // return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    // return Color(1, 0.41, 0.12) * (parallelism + 1) * 0.5;
}

Sphere::Sphere(Point3 location, double radius) : Shape(location), radius(radius) { }
