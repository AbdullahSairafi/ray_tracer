#include "camera.h"
// #include "vector.h"
// #include "ray.h"

using namespace std;

PrespectiveCamera::PrespectiveCamera(Point origin, Point target, Vec3d upguide)
    : m_origin{origin}, m_target{target}, m_upguide{upguide} 
{
    b_forward = (target - origin).normalize();
    b_right = cross(b_forward, m_upguide).normalize();
    b_up = cross(b_right, b_forward).normalize();

}
Ray PrespectiveCamera::make_ray(double u, double v){
    Vec3d dir = (u * b_right) + (v * b_up) + b_forward; // note focal length = 1 for camera.
    return Ray(m_origin, dir.normalize());
}

void PrespectiveCamera::print_info(){
    cout << "forwad = " << b_forward << endl;
    cout << "right  = " << b_right << endl;
    cout << "up     = " << b_up << endl;
    cout << "origin = " << m_origin << endl;
    cout << "target = " << m_target << endl;
}
// void PrespectiveCamera::update_origin(Point origin){
    
// }

// void PrespectiveCamera::update_target(Point target){
    
// }

// void PrespectiveCamera::update_basis(){

// }