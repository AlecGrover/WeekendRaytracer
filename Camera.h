//
// Created by alecg on 7/18/2022.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include "Vector3.h"
#include "util.h"
#include "Ray.h"
#include "Rotation.h"

class Camera {
public:
    double aspect_ratio;
    double viewport_height;
    double viewport_width;
    double focal_length;
    double vfov;
    Rotation rotation;
public:
    explicit Camera(double aspect_ratio= 1.6, double vh= 500, double focal_length= 1.0, Point3 origin= ZERO_VECTOR, Vector3 camera_rotation= ZERO_VECTOR);
    Ray get_ray(double x, double y) const;
    static void write_color(std::ostream &os, Color pixel_color, int samples);
    void write_color_gamma_corrected(std::ostream &os, Color pixel_color, int samples);
private:
    Point3 origin;
    Point3 scan_start;
    Vector3 horizontal_vector;
    Vector3 vertical_vector;



};


#endif //RAYTRACER_CAMERA_H
