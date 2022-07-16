//
// Created by alecg on 7/10/2022.
// [Summary]: Main class for the One Weekend Raytracer project. Project follows the guidelines of Steve Hollasch from
//            https://raytracing.github.io/books/RayTracingInOneWeekend.html. Extended, modified, and otherwise tweaked
//            by myself for practice purposes. - alecg
//

#include <iostream>
#include "Color.h"
#include "Ray.h"
#include "Vector3.h"

Color ray_color(const Ray& r) {
    Vector3 unit_direction = unit_vector(r.get_direction());
    auto t= 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {
    /*
     *  Begin Project Code
     */

#pragma region ImageParameters

    // Image Constants

    // Note: Using a 16:10 aspect ratio for a cleaner number, can easily be converted to 16:9
    const auto aspect_ratio= 1.6;

    const int image_height= 500;
    const int image_width= static_cast<int>(image_height * aspect_ratio);

#pragma endregion ImageParameters

#pragma region CameraParameters

    auto viewport_height= 2.0;
    auto viewport_width= viewport_height * aspect_ratio;
    auto focal_length= 1.0;

    Point3 origin= {0, 0, 0};
    Vector3 width_vector= {viewport_width, 0, 0};
    Vector3 height_vector= {0, viewport_height, 0};
    Vector3 focal_vector= {0, 0, -focal_length};

    // Scan starts in bottom left
    Vector3 scan_start_corner= origin - 0.5 * width_vector - 0.5 * height_vector + focal_vector;

#pragma endregion CameraParameters

#pragma region Renderer

    std::cout << "P3\n" << image_width << ' ' << image_height << ' ' << "\n255\n";

    for (int y= image_height - 1; y >= 0; y--) {
        std::cerr << "\rScanlines Remaining: " << y << ' ' << std::flush;
        for (int x= image_width - 1; x >= 0; x--) {
            double x_progress= x / (image_width - 1.0);
            double y_progress= y / (image_height - 1.0);

            Ray r(origin, scan_start_corner + x_progress * width_vector + y_progress * height_vector - origin);
            Color pixel= ray_color(r);
            write_color(std::cout, pixel);
        }
    }

    std::cerr << "\nDone." << std::endl;

#pragma endregion Renderer

    /*
     *  End Project Code
     */
    return 0;
}
