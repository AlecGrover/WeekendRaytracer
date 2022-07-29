//
// Created by alecg on 7/15/2022.
//

#include "Shape.h"

Shape::Shape(Point3 location, std::shared_ptr<Material> material) : location(location), material(material) { }

Color Shape::color_from_ray(Ray r) {
    return {1.0, 0.41, 0.12};
}

Vector3 Shape::get_normal_at_point(Point3 point) const {
    return unit_vector(point - location);
}
