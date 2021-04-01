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
    b_forward = (m_target - m_origin).normalize();
    b_right = cross(b_forward, m_upguide).normalize();
    b_up = cross(b_right, b_forward).normalize();
}

void PrespectiveCamera::move_camera(char direction){
    double c = 0.05; // offset step size
    Vec3d offset;
    switch (direction)
    {
    case 'u': // up
        offset = b_up * c;
        m_origin += offset;
        m_target += offset;
        break;
    case 'l': // left
        offset = b_right * c;
        m_origin -= offset;
        m_target -= offset;
        break;
    case 'r': // right
        offset = b_right * c;
        m_origin += offset;
        m_target += offset;
        break;
    case 'd': // down
        offset = b_up * c;
        m_origin -= offset;
        m_target -= offset;
        break;
    case 'f': // forward
        offset = b_forward * c;
        m_origin += offset;
        break;
    case 'b': // backward
        offset = b_forward * c;
        m_origin -= offset;
        break;
    default: // do nothing
        break;
    }
}

void PrespectiveCamera::move_target(char direction){
    double c = 0.05;
    Vec3d offset;
    switch (direction)
    {
    case 'u':
        offset = b_up * c;
        m_target += offset;
        set_basis(m_upguide);
        break;
    case 'l':
        offset = b_right * c;
        m_target -= offset;
        set_basis(m_upguide);
        break;
    case 'r':
        offset = b_right * c;
        m_target += offset;
        set_basis(m_upguide);
        break;
    case 'd':
        offset = b_up * c;
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
