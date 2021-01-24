#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "ray.h"

class Camera{
public:
    virtual make_ray(double u, double v) const = 0;
};

class PrespectiveCamera : public Camera {
public:
    PreespectiveCamera(Point o, Point t, Vec3d _up);
    virtual Ray make_ray(double u, double v) const override;
    void update_origin();
    void update_target();
private:
    Vec3d b_up;
    Vec3d b_right;
    Vec3d b_forward;
    Point origin;
    Point target;
    constexpr Vec3d upguide;
    void update_basis(); // update basis when changing target or origin
};
#endif