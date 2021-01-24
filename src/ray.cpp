#include "ray.h"

using namespace std;

Ray::Ray(Point &o, Vec3d &d) : orig{o}, dir{d}
{
}

const Point& Ray::get_orig() const {
    return orig;
}

const Vec3d& Ray::get_dir() const {
    return dir;
}
