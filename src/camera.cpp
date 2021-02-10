#include "camera.h"

using namespace std;

PrespectiveCamera::PrespectiveCamera(const Point &origin, const Point &target, const Vec3d &upguide)
    : m_origin{origin}, m_target{target}, m_upguide{upguide} 
{
   set_basis(upguide);
}
Ray PrespectiveCamera::make_ray(double u, double v){
    Vec3d dir = (u * b_right) + (v * b_up) + b_forward; // note focal length = 1 for camera.
    return Ray(m_origin, dir.normalize());
}

void PrespectiveCamera::set_basis(const Vec3d &upguide){
    b_forward = (target - origin).normalize();
    b_right = cross(b_forward, m_upguide).normalize();
    b_up = cross(b_right, b_forward).normalize();
}

void PrespectiveCamera::move_camera(char direction){
    double c = 0.2; // offset step size
    switch (direction)
    {
    case 'u': // up
        Vec3d offset = b_up * c;
        m_origin += offset;
        m_target += offset;
        break;
    case 'l': // left
        Vec3d offset = b_right * c;
        m_origin -= offset;
        m_target -= offset;
        break;
    case 'r': // right
        Vec3d offset = b_right * c;
        m_origin += offset;
        m_target += offset;
        break;
    case 'd': // down
        Vec3d offset = b_up * c;
        m_origin += offset;
        m_target += offset;
        break;
    case 'f': // forward
        Vec3d offset = b_forward * c;
        m_origin += offset;
        break;
    case 'b': // backward
        Vec3d offset = b_forward * c;
        m_origin -= offset;
        break;
    default: // do nothing
        break;
    }
}

void PrespectiveCamera::move_target(char direction){
    double c = 0.2;
    switch (direction)
    {
    case 'u':
        Vec3d offset = b_up * c;
        m_target += offset;
        set_basis(m_upguide);
        break;
    case 'l':
        Vec3d offset = b_right * c;
        m_target -= offset;
        set_basis(m_upguide);
        break;
    case 'r':
        Vec3d offset = b_right * c;
        m_target += offset;
        set_basis(m_upguide);
        break;
    case 'd':
        Vec3d offset = b_up * c;
        m_target -= offset;
        set_basis(m_upguide);
        break;
    default:
        break;
    }
}
void PrespectiveCamera::print_info(){
    cout << "forwad = " << b_forward << endl;
    cout << "right  = " << b_right << endl;
    cout << "up     = " << b_up << endl;
    cout << "origin = " << m_origin << endl;
    cout << "target = " << m_target << endl;
}
