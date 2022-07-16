//
// Created by alecg on 7/15/2022.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "Vector3.h"
#include <iostream>

void write_color(std::ostream &os, Color pixel_color) {
    os << static_cast<int>(255.99 * pixel_color.x()) << ' '
       << static_cast<int>(255.99 * pixel_color.y()) << ' '
       << static_cast<int>(255.99 * pixel_color.z()) << '\n';
}

#endif //RAYTRACER_COLOR_H
