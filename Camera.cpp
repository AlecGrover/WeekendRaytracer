//
// Created by alecg on 7/18/2022.
//

#include "Camera.h"
#include <math.h>

Camera::Camera(double aspect_ratio, double vfov, double focal_length, Point3 origin)
 : aspect_ratio(aspect_ratio), vfov(vfov), focal_length(focal_length), origin(origin){
    auto t= deg2rad(vfov);
    auto h= tan(t/2.0);
    viewport_height= 2.0 * h;
    viewport_width= aspect_ratio * viewport_height;

    horizontal_vector= Vector3(viewport_width, 0.0, 0.0);
    vertical_vector= Vector3(0.0, viewport_height, 0.0);
    scan_start= origin - Vector3(viewport_width / 2.0, viewport_height / 2.0, focal_length);
}

Ray Camera::get_ray(double x, double y) const {
    return { origin, scan_start + x * horizontal_vector + y * vertical_vector - origin };
}

void Camera::write_color(std::ostream &os, Color pixel_color, int samples)  {
    auto r= pixel_color.r();
    auto g= pixel_color.g();
    auto b= pixel_color.b();

    auto scale= 1.0 / samples;
    r *= scale;
    g *= scale;
    b *= scale;

    os << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
       << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
       << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';

}

void Camera::write_color_gamma_corrected(std::ostream &os, Color pixel_color, int samples) {
    auto scale= 1.0 / samples;
    write_color(os, Color(sqrt(scale * pixel_color.r()), sqrt(scale * pixel_color.g()), sqrt(scale * pixel_color.b())), 1);

}
