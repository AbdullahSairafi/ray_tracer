#ifndef SHAPES_H
#define SHAPES_H
#include <iostream>
#include "ray.h"
#include "vector.h"
#include "color.h"

using namespace std;

enum class ShapeType {
    SPHERE,
    PLANE,
    CYLINDER,
    CONE,
    TRINAGLE
};

// shape class (an abstract class) that will be utilized as an iterator
class Shape
{

public:
    Shape(Color col, ShapeType t);
    virtual ~Shape() = default;
    virtual Vec3d normal(const Point &p) const = 0;
    virtual bool intersect(Ray &r, double &t, double t_low, double t_up) = 0;
    
    ShapeType get_type() const {return m_type;}
    Color get_color() const {return m_col;}
 

private:
    Color m_col;
    ShapeType m_type;
};

class Sphere : public Shape {

public:
    /* constructor
     * @c: center of the sphere.
     * @rad: radius
     * @col: color    
    */
    Sphere(Point cen, double rad, Color col);
    
    /* normal: Return a normal vector to a given point on the sphere.
     * @p: point to calculate normal at.
    */
    virtual Vec3d normal(const Point &p) const override;

    /* intersect: finds an intersection point with the sphere if exsists
     * @r: ray to to be check if intersects the sphere.
     * @t: shifting factor to find the point of intersection relative 
     * to ray r. p(t) = origin + t * direction
     * note that t should be a postive value [0, inf)
    */
    virtual bool intersect(Ray &r, double &t, double t_low, double t_up) override;

    const Point& get_center() const {return m_cen;}
    double get_radius() const {return m_rad;}

private:
    Point m_cen;
    double m_rad;
};


class Triangle : public Shape {
public:
    // constructor takes three vertices (positions)
    Triangle(const Vec3d &a, const Vec3d &b, const Vec3d &c, const Color &col);
    virtual Vec3d normal(const Point &p) const override;
    virtual bool intersect(Ray &r, double &t, double t_low, double t_up) override;

private:
    Vec3d m_vertices[3];
    Vec3d m_normal;
    double beta;
    double gamma;
};
#endif