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
    PrespectiveCamera(const Point &origin, const Point &target, const Vec3d &upguide);
    Ray make_ray(double u, double v);
    const Point& get_orig(){return m_origin;}
    // candidates for inline functions
    void set_origin(const Point &origin){m_origin = origin;}
    void set_target(const Point &target){m_target = target;}
    void set_upguide(const Vec3d &upguide){m_upguide = upguide;}
    // for debugging purposes
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