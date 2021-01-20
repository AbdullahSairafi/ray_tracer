#include <iostream>
#include "vector.h"
#include <cmath>

using namespace std;

Vec3d::Vec3d(double x, double y, double z) 
    : m_x{x}, m_y{y}, m_z{z} 
{
    // no need for assignment here
}

Vec3d::Vec3d(const Vec3d &v) : m_x{v.m_x}, m_y{v.m_y}, m_z{v.m_z}
{
}
// getters
double Vec3d::get_x() const {
    return m_x;
}

double Vec3d::get_y() const {
    return m_y;
}

double Vec3d::get_z() const {
    return m_z;
}

// setters 
void Vec3d::set_x(double x){
    m_x = x;
}

void Vec3d::set_y(double y){
    m_y = y;
}

void Vec3d::set_z(double z){
    m_z = z;
}


// l2norm and normalize
double Vec3d::l2norm(){
    return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

Vec3d& Vec3d::normalize(){
    double len = l2norm();
    *this = (*this) / len;
    return *this;
}


// overloaded assignment operator
Vec3d& Vec3d::operator=(const Vec3d &v){
    if(this == &v){ // to avoid self assignment. Problematic with dynamically allocated memory.
        return *this;
    }
    m_x = v.m_x;
    m_y = v.m_y;
    m_z = v.m_z;

    return *this;
}
// dot and cross products
double dot(const Vec3d &v1, const Vec3d &v2){
    return (v1.m_x * v2.m_x 
            + v1.m_y * v2.m_y 
            + v1.m_z * v2.m_z);
}

Vec3d cross(const Vec3d &v1, const Vec3d &v2){
    double i = v1.m_y * v2.m_z - v1.m_z * v2.m_y;
    double j = v1.m_z * v2.m_x - v1.m_x * v2.m_z;
    double k = v1.m_x * v2.m_y - v1.m_y * v2.m_x;
    return Vec3d(i, j, k);
}
// printing 
ostream& operator<<(ostream &out, const Vec3d &v){
    out << "<" << v.m_x << ", " << v.m_y << ", " << v.m_z << ">";
    return out;
}

// overloaded operators
Vec3d operator+(const Vec3d &v1, const Vec3d &v2){
    return Vec3d(v1.get_x() + v2.get_x(),
                 v1.get_y() + v2.get_y(), 
                 v1.get_z() + v2.get_z());
}

Vec3d operator-(const Vec3d &v1, const Vec3d &v2){
    return Vec3d(v1.get_x() - v2.get_x(),
                 v1.get_y() - v2.get_y(), 
                 v1.get_z() - v2.get_z());
}

Vec3d operator*(const Vec3d &v, double c){
    return Vec3d(v.get_x() * c, v.get_y() * c, v.get_z() * c);
}

Vec3d operator*(double c, const Vec3d &v){
    return Vec3d(v.get_x() * c, v.get_y() * c, v.get_z() * c);
}

Vec3d operator/(const Vec3d &v, double c){
    return Vec3d(v.get_x() / c, v.get_y() / c, v.get_z() / c);
}