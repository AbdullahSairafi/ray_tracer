#include "shapes.h" 
#include "ray.h"
#include <algorithm> // min()
#include <cmath>

Shape::Shape(Color col, ShapeType t) : m_col{col}, m_type{t}
{
}

Sphere::Sphere(Point cen, double rad, Color col) 
    : Shape{col, ShapeType::SPHERE}, m_cen{cen}, m_rad{rad} 
{
}

Vec3d Sphere::normal(const Point &p) const {
    Vec3d normal = 2 * (p - m_cen);
    normal.normalize();
    return normal;
}

bool Sphere::intersect(Ray &r, double &t){
    bool hit = false;
    // cout << "ray dir = " << r.get_dir() << endl;
    double a = dot(r.get_dir(), r.get_dir());
    double b = 2 * dot(r.get_orig() - m_cen, r.get_dir());
    double c = dot(r.get_orig() - m_cen, r.get_orig() - m_cen) - m_rad * m_rad;

    double discriminant = b * b - 4 * a * c;
    // cout << discriminant << endl;
    if(discriminant > 0.0 ) { // there is a solution for quadratic formula
        double t0 = (-b - sqrt(discriminant)) / (2 * a);
        double t1 = (-b + sqrt(discriminant)) / (2 * a);

        if(t0 < 0.0 && t1 < 0.0){ // both are negative
            hit = false;
        }
        else if(t0 < 0.0 && t1 >= 0.0){
            hit = true;
            t = t1;
        }
        else{ // both are positive
            hit = true;
            t = min(t0, t1);
        }
    }

    return hit;
}

