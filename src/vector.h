#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

class Vec3d {
    
public:
    // Default constructor
    Vec3d(double x = 0.0, double y = 0.0, double z = 0.0);
    // copy constructor
    Vec3d(const Vec3d &v);

    // getters
    double get_x() const;
    double get_y() const;
    double get_z() const;

    // setters
    void set_x(double x);
    void set_y(double y);
    void set_z(double z);

    // l2norm and normalize
    double l2norm(); // length of vector
    Vec3d& normalize(); // normalize the vector
    
    // overloaded assignment operator
    Vec3d& operator=(const Vec3d &v);

    // vector operations dot, cross as friend functions
    friend double dot(const Vec3d &v1, const Vec3d &v2);
    friend Vec3d cross(const Vec3d &v1, const Vec3d &v2);

    // printing
    friend ostream& operator<<(ostream &out, const Vec3d &v);

    //comparison
    friend bool operator==(const Vec3d &v1, const Vec3d &v2);
    friend bool operator!=(const Vec3d &v1, const Vec3d &v2);
private:
    double m_x;
    double m_y;
    double m_z;
};

 // overloaded operators +, -, *, /
Vec3d operator+(const Vec3d &v1, const Vec3d &v2);
Vec3d operator-(const Vec3d &v1, const Vec3d &v2);
Vec3d operator*(const Vec3d &v, double c); // vector * c
Vec3d operator*(double c, const Vec3d &v); // c * vector
Vec3d operator/(const Vec3d &v, double c);

typedef Vec3d Point;

#endif

