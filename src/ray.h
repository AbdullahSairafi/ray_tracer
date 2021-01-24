#ifndef RAY_H
#define RAY_H
#include "vector.h"
class Ray{
public:
    Ray(Point &o, Vec3d &d);
    // Ray(Point o, Vec3d d);
    const Point& get_orig() const;
    const Vec3d& get_dir() const;
private:
    Point orig;
    Vec3d dir;
};

#endif