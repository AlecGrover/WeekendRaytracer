//
// Created by alecg on 7/10/2022.
// [Summary]: Main class for the One Weekend Raytracer project. Project follows the guidelines of Steve Hollasch from
//            https://raytracing.github.io/books/RayTracingInOneWeekend.html. Extended, modified, and otherwise tweaked
//            by myself for practice purposes. - alecg
//

#include <iostream>
#include <vector>
#include "Color.h"
#include "Ray.h"
#include "Vector3.h"
#include "Shape.h"
#include "Sphere.h"

Color ray_color(const Ray& r) {
    Vector3 unit_direction = unit_vector(r.get_direction());
    auto t= 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

//Shape* return_first_intersected_shape(std::vector<Shape*>* shapes, Ray r) {
//    for (auto & shape : *shapes) {
//        if (shape->b_ray_hit(r)) return shape;
//    }
//    return nullptr;
//}

bool get_first_intersected_color(const std::vector<Shape*>& shapes, Ray& r, Color& out, double t_min, double t_max) {
    hit hit_out;
    double closest_hit_distance = std::numeric_limits<double>::max();
    Shape* hit_shape= nullptr;
    hit closest_hit;
    for (auto shape : shapes) {
        if (shape->b_ray_hit(r, t_min, t_max, hit_out)) {
            if (hit_out.hit_location.length_squared() < closest_hit_distance) {
                closest_hit= hit_out;
                hit_shape= shape;
            }
        }
    }

    if (hit_shape == nullptr) return false;

    out= hit_shape->color_from_hit(closest_hit);
    return true;
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

#pragma region SceneGeometry

    std::vector<Shape*> Shapes;
    // Scene shapes
    Sphere sphere_1 = Sphere(Point3(0, 0, -10), 5);
    Shapes.push_back(&sphere_1);


#pragma endregion SceneGeometry


#pragma region Renderer

    const double T_MIN= 1;
    const double T_MAX= 100;

    std::cout << "P3\n" << image_width << ' ' << image_height << ' ' << "\n255\n";
    hit out;

    for (int y= image_height - 1; y >= 0; y--) {
        std::cerr << "\rScanlines Remaining: " << y << ' ' << std::flush;
        for (int x= image_width - 1; x >= 0; x--) {
            double x_progress= x / (image_width - 1.0);
            double y_progress= y / (image_height - 1.0);

            Ray r(origin, scan_start_corner + x_progress * width_vector + y_progress * height_vector - origin);
            Color pixel;

            if (!get_first_intersected_color(Shapes, r, pixel, T_MIN, T_MAX)) pixel= ray_color(r);
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
