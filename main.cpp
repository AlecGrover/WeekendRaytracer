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
#include "Shape.h"
#include "Sphere.h"
#include "Camera.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

Ray get_unit_sphere_rejection_ray(const hit &parameters);

Ray get_random_polar_spherical_ray(const hit &parameters);

Ray get_hemispherical_ray(const hit &parameters);

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
    double closest_hit_distance = MAX_DOUBLE;
    Shape* hit_shape= nullptr;
    hit closest_hit;
    for (auto shape : shapes) {
        if (shape->b_ray_hit(r, t_min, t_max, hit_out)) {
            if (hit_out.hit_location.length_squared() < closest_hit_distance) {
                closest_hit= hit_out;
                closest_hit_distance= hit_out.hit_location.length_squared();
                hit_shape= shape;
            }
        }
    }

    if (hit_shape == nullptr) {
        out= ray_color(r);
        return false;
    }

    out= hit_shape->color_from_hit(closest_hit);
    return true;
}

bool get_first_hit(const std::vector<Shape*>& shapes, const Ray& r, hit& out, double t_min= 0.001, double t_max= INFINITY_DOUBLE) {
    hit hit_out;
    double closest_hit_distance = MAX_DOUBLE;
    hit closest_hit;
    bool hit_something= false;
    for (auto shape : shapes) {
        if (shape->b_ray_hit(r, t_min, t_max, hit_out)) {
            if ((hit_out.hit_location - r.get_origin()).length_squared() < closest_hit_distance) {
                hit_something= true;
                closest_hit= hit_out;
                closest_hit_distance= (hit_out.hit_location - r.get_origin()).length_squared();
            }
        }
    }

    out= closest_hit;

    return hit_something;
}

Color get_color(const Ray& r, std::vector<Shape*>& shapes, int depth, diffuse_renderer renderer=NORMALIZED_RANDOM_POLAR, double t_min= 0.001, double t_max= INFINITY_DOUBLE) {
    hit parameters;
    if (depth <= 0) return {0.0, 0.0, 0.0 };
    if (get_first_hit(shapes, r, parameters, t_min, t_max)) {
        Ray bounce_ray;
        switch (renderer) {
            case (NORMALIZED_RANDOM_POLAR):
                bounce_ray= get_random_polar_spherical_ray(parameters);
                break;
            case (NORMALIZED_UNIT_SPHERICAL):
                bounce_ray= get_unit_sphere_rejection_ray(parameters);
                break;
            default:
                bounce_ray = get_hemispherical_ray(parameters);
                break;
        }

        return 0.5 * get_color(bounce_ray, shapes, depth - 1, renderer, t_min, t_max);
    }

    auto t = 0.5 * unit_vector(r.get_direction()).y() + 1.0;
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

Color get_material_color(const Ray& r, const  std::vector<Shape*>& shapes, int depth) {

    if (depth <= 0) return BLACK;

    hit parameters;

    if (get_first_hit(shapes, r, parameters)) {

        Ray scatter;
        Color attenuation;
        if (parameters.material->scatter(r, parameters, attenuation, scatter))
            return attenuation * get_material_color(scatter, shapes, depth - 1);

        return BLACK;
    }

    Vector3 direction= unit_vector(r.get_direction());
    auto t = 0.5 * (direction.y() + 1.0);
    return (1.0 - t) * WHITE + t * TURQUOISE;

}


Ray get_hemispherical_ray(const hit &parameters) {
    Ray bounce_ray= Ray(parameters.hit_location, random_in_hemisphere(parameters.normal) + parameters.normal);
    return bounce_ray;
}

Ray get_random_polar_spherical_ray(const hit &parameters) {
    Ray bounce_ray= Ray(parameters.hit_location, unit_vector(random_polar_vector(1) + parameters.normal));
    return bounce_ray;
}

Ray get_unit_sphere_rejection_ray(const hit &parameters) {
    Ray bounce_ray= Ray(parameters.hit_location, random_in_unit_sphere_normalized() + parameters.normal);
    return bounce_ray;
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
    const int samples= 12;

#pragma endregion ImageParameters

#pragma region CameraParameters

    auto focal_length= 2.0;
    auto fov= 100.0;
    Camera camera(aspect_ratio, fov / aspect_ratio, focal_length);
    // Scan starts in bottom left

#pragma endregion CameraParameters

#pragma region SceneGeometry


    auto m_ground= std::make_shared<Lambertian>(BROWN);
    auto m_center= std::make_shared<Lambertian>(0.75 * SALMON);
    auto m_right= std::make_shared<Metal>(0.8 * WHITE, 0.05);
    auto m_left= std::make_shared<Metal>(BEIGE * 0.8, 0.6);
    auto m_front= std::make_shared<Dielectric>(WHITE, 1.5);

    std::vector<Shape*> Shapes;
    // Scene shapes
    Sphere sphere_center= Sphere(Point3(0, 0, -22), 5, m_center);
    Sphere sphere_right= Sphere(Point3(-10, -1, -20), 4, m_right);
    Sphere sphere_left= Sphere(Point3(15, 3, -30), 8, m_front);
    Sphere ground_sphere= Sphere(Point3(0, -205, -20), 200, m_ground);
    Sphere sphere_front= Sphere(Point3(0, -3.5, -15), 1.5, m_front);
    Shapes.push_back(&sphere_front);
    Shapes.push_back(&sphere_center);
    Shapes.push_back(&sphere_left);
    Shapes.push_back(&sphere_right);
    Shapes.push_back(&ground_sphere);


#pragma endregion SceneGeometry


#pragma region Renderer

    const double T_MIN= 1;
    const double T_MAX= 100;
    const int MAX_DEPTH= 50;

    std::cout << "P3\n" << image_width << ' ' << image_height << ' ' << "\n255\n";
    hit out;

    for (int y= image_height - 1; y >= 0; y--) {
        std::cerr << "\rScanlines Remaining: " << y << ' ' << std::flush;
        for (int x= 0; x < image_width; x++) {
            Color pixel= {};
            for (int s= 0; s < samples; s++) {
                Color sample= {};
                double x_sample= (x + cpp_random_normalized()) / (image_width - 1.0);
                double y_sample= (y + cpp_random_normalized()) / (image_height - 1.0);
                Ray r= camera.get_ray(x_sample, y_sample);
                get_first_intersected_color(Shapes, r, sample, T_MIN, T_MAX);
                pixel += get_material_color(r, Shapes, MAX_DEPTH);
            }

            camera.write_color_gamma_corrected(std::cout, pixel, samples);

        }
    }

    std::cerr << "\nDone." << std::endl;

#pragma endregion Renderer

    /*
     *  End Project Code
     */
    return 0;
}
