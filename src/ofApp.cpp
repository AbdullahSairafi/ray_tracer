#include "ofApp.h"
#include <limits>
#include <algorithm> 
#include <cmath>
//--------------------------------------------------------------
void ofApp::setup(){
    
    colorPixels.allocate(w, h, OF_PIXELS_RGB);
    // texColor.allocate(colorPixels);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofSetHexColor(0xffffff);
	texColor.draw(0, 0);
}

void ofApp::add_shapes(){
    Sphere *sph0{new Sphere{Point(-1, 0.5,0.5), 0.5, Color(200, 0, 0)}};
    Sphere *sph1{new Sphere{Point(1, 0.5,0.5), 0.5, Color(25, 79, 43)}};
    pShapes.push_back(sph0);
    pShapes.push_back(sph1);
}

bool ofApp::check_intersection(Ray view_ray, Shape *hit_obj, double &t_low, double t_up){
    bool hit = false;
    double t;
    for(int i = 0; i < pShapes.size(); i++){
        if(pShapes[i]->intersect(view_ray, t) && t_low <= t && t < t_up){
            hit = true;
            t_up = t;
            hit_obj = pShapes[i]; // update hit object
        }
    }
    if(hit_obj == nullptr){ // enforce a valid object in hit_obj pointer.
        return false;
    }
    return hit;
}

Color ofApp::shading_model(Ray view_ray, Shape *hit_obj, double t){
    Point intersection_pt = view_ray.get_orig() + t * view_ray.get_dir();
    Color pix_col = hit_obj->get_color() * ambient_intensity;
    for(int i = 0; i < lights.size(); i++){
        if(!is_shadow(lights[i],  intersection_pt)){
            pix_col = pix_col + diffuse_color(lights[i], intersection_pt, hit_obj) + specular_color(lights[i], intersection_pt, hit_obj);
        }
    }
    
}

bool ofApp::is_shadow(const Point &light_src, const Point &intersection_pt){
    bool is_shadow = false;
    double epsilon = 0.001;
    Shape *shadow_obj = nullptr;
    Vec3d light_dir = (light_src - intersection_pt).normalize();
    // generate shadow ray for light source
    Point sh_ray_origin = intersection_pt + light_dir * epsilon; // add offset to avoid self-intersection
    Ray shadow_ray{sh_ray_origin, light_dir};
    is_shadow = check_intersection(shadow_ray, shadow_obj, 0.0, numeric_limits<double>::infinity);
    return is_shadow;
}

Color ofApp::diffuse_color(const Point &light, const Point &intersection_pt, Shape *hit_obj){
    Vec3d light_dir = (light - intersection_pt).normalize();
    Vec3d normal = hit_obj->normal();
    Color diff_col = hit_obj->get_color() * light_intensity * std::max(0.0, dot(normal, light_dir));
    return diff_col;
}

Color ofApp::specular_color(const Point &light, const Point &intersection_pt, Shape *hit_obj){
    // for info look up this wiki link
    Vec3d light_dir = (light - intersection_pt).normalize();
    Vec3d v = (camera.get_orig() - intersection_pt).normalize();
    Vec3d h = (light_dir + v).normalize();
    Vec3d normal = hit_obj->normal();
    Color spec_col = Color(128, 128, 128) * light_intensity * std::pow(std::max(0.0, dot(normal, h)));
    return spec_col;
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // when exsiting, free allocated resources.
    if(key == 27){
        for(int i = 0; i < pShapes.size(); i++){
            delete pShapes[i];
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
