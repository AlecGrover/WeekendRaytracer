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

static const Color BLACK= Color(0, 0, 0);
static const Color WHITE= Color(1, 1, 1);
static const Color RED= Color(1, 0, 0);
static const Color GREEN= Color(0, 1, 0);
static const Color BLUE= Color(0, 0, 1);
static const Color CYAN= Color(0, 1, 1);
static const Color PURPLE= Color(1, 0, 1);
static const Color YELLOW= Color(1, 1, 0);
static const Color GREY= Color(0.5, 0.5, 0.5);
static const Color HOT_PINK= Color(1, 0, 0.5);
static const Color ORANGE= Color(1, 0.5, 0);
static const Color LIME= Color(0.5, 1.0, 0);
static const Color MINT= Color(0, 1, 0.5);
static const Color SAPPHIRE= Color(0, 0.5, 1);
static const Color INDIGO= Color(0.5, 0, 1);
static const Color SKY_BLUE= Color(0.5, 0.5, 1);
static const Color SALMON= Color(1, 0.5, 0.5);
static const Color PALE_GREEN= Color(0.5, 1, 0.5);
static const Color BROWN= Color(0.4, 0.3, 0.2);
static const Color BEIGE= Color(1, 0.8, 0.6);
static const Color PINK= Color(1, 0.6, 0.8);
static const Color AQUA= Color(0.6, 1.0, 0.8);
static const Color NOTEPAD= Color(0.8, 1, 0.6);
static const Color VIOLET= Color(0.8, 0.6, 1);
static const Color TURQUOISE= Color(0.6, 0.8, 1);







#endif //RAYTRACER_COLOR_H
