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

bool Sphere::intersect(Ray &r, double &t, double t_low, double t_up){
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
    if(t < t_low || t > t_up){
        return false;
    }
    return hit;
}

Triangle::Triangle(const Vec3d &a, const Vec3d &b, const Vec3d &c, const Color &col) 
    : Shape{col, ShapeType::TRINAGLE}
{
    m_vertices[0] = a;
    m_vertices[1] = b;
    m_vertices[2] = c;
    m_normal = cross(b - a, c - a).normalize();
}

Vec3d Triangle::normal(const Point &p) const {
    return m_normal;
}

bool Triangle::intersect(Ray &r, double &t, double t_low, double t_up){
    
    // check if ray and triangle normal are parallel (no intersection)
    // if(abs(cross(r.get_dir(), m_normal)) < 0.0001){
    //     return false;
    // }
    Vec3d AB = m_vertices[0] - m_vertices[1]; // A - B
    Vec3d AC = m_vertices[0] - m_vertices[2]; // A - C
    Vec3d AE = m_vertices[0] - r.get_orig(); // A - origin
    Vec3d dir = r.get_dir();

    
    // constants
    double k0 = AC.get_y() * dir.get_z() - dir.get_y() * AC.get_z();
    double k1 = AC.get_z() * dir.get_x() - dir.get_z() * AC.get_x();
    double k2 = AC.get_x() * dir.get_y() - dir.get_x() * AC.get_y();
    double k3 = AB.get_x() * AE.get_y() - AB.get_y() * AE.get_x();
    double k4 = AB.get_z() * AE.get_x() - AB.get_x() * AE.get_z();
    double k5 = AB.get_y() * AE.get_z() - AB.get_z() * AE.get_y();

    double M = AB.get_x() * k0 + AB.get_y() * k1 + AB.get_z() * k2;
    beta = (AE.get_x() * k0 + AE.get_y() * k1 + AE.get_z() * k2) / M;
    gamma = (dir.get_z() * k3 + dir.get_y() * k4 + dir.get_x() * k5) / M;
    t = -1 * (AC.get_z() * k3 + AC.get_y() * k4 + AC.get_x() * k5) / M;

    if(t < t_low || t > t_up){
        return false;
    }
    if(gamma < 0.0 || gamma > 1.0){
        return false;
    }
    if(beta < 0.0 || beta > 1.0 - gamma){
        return false;
    }

    return true;
   
}

Mesh::Mesh(vector<Vec3d> *positions_p, vector<Vec3d> *normals_p, vector<Vec2d> *texcoords_p, 
         Face_Indices *indices_p)
        : m_positions_p{positions_p}, m_normals_p{normals_p}, m_texcoords_p{texcoords_p},
         m_indices_p{indices_p}, Shape{Color(0,0,0), ShapeType::TRINAGLE}
{
    num_verts = m_positions_p->size();
    num_triangles = m_indices_p->positions_v.size();
}

Vec3d Mesh::normal(const Point &p) const {
    return Vec3d();
}

bool Mesh::intersect(Ray &r, double &t, double t_low, double t_up){
    return true;
}