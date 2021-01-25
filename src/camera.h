#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "ray.h"

// class Camera{
// public:
//     virtual make_ray(double u, double v) const = 0;
// };

class PrespectiveCamera{
public:
    PrespectiveCamera(Point origin, Point target, Vec3d upguide);
    virtual Ray make_ray(double u, double v) const override;
    // void update_origin(Point origin);
    // void update_target(Point target);
private:
    Vec3d b_up;
    Vec3d b_right;
    Vec3d b_forward;
    Point m_origin;
    Point m_target;
    constexpr Vec3d m_upguide;
    // void update_basis(); // update basis when changing target or origin
};
#endif