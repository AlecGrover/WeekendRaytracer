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
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {
    /*
     *  Begin Project Code
     */

#pragma region Image

    // Image Constants
    const int ImageHeight= 256;
    const int ImageWidth= 256;
    std::cout << "P3\n" << ImageHeight << ' ' << ImageWidth << "\n255\n";

    double red, green;
    int OutRed, OutGreen;
    const int OutBlue= 64;

    // Renderer
    for (int y= 0; y < ImageHeight; y++) {
        std::cerr << "\rScanlines remaining: " << 256 - y << ' ' << std::flush;
        for (int x= 0; x < ImageWidth; x++) {

            Color pixel(double(y)/(ImageWidth - 1.0), double(x)/(ImageHeight - 1.0), 0.25);
            write_color(std::cout, pixel);
        }
    }
    std::cerr << "\nDone.\n";

#pragma endregion Image



    /*
     *  End Project Code
     */
    return 0;
}
