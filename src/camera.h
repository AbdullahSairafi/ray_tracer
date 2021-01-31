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
    Ray make_ray(double u, double v);
    const Point& get_orig();
    void set_origin(Point origin);
    void set_target(Point target);
    void set_upguide(Vec3d upguide);
    void print_info();
private:
    Vec3d b_up;
    Vec3d b_right;
    Vec3d b_forward;
    Point m_origin;
    Point m_target;
    Vec3d m_upguide;
    // void update_basis(); // update basis when changing target or origin
};
#endif