//
// Created by alecg on 7/15/2022.
//

#include "Ray.h"

Ray::Ray(const Point3 &origin, const Vector3 &direction) : origin(origin), direction(direction){ }
Ray::Ray() { }

Point3 Ray::get_origin() const {
    return origin;
}

Vector3 Ray::get_direction() const {
    return direction;
}

void Ray::set_origin(Point3 new_origin) {
    origin= new_origin;
}

void Ray::set_direction(Vector3 new_direction) {
    direction= new_direction;
}

Point3 Ray::at(double t) const {
    return origin + t * direction;
}
