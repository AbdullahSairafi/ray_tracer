#include "ofApp.h"
#include <limits>
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
    Sphere *sph1{new Sphere{Point(1, 0.5,0.5), 0.5, Color(0, 0, 200)}};
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

    return hit;
}

Color ofApp::shading_model(Ray view_ray, Shape *hit_obj, double t){
    Point intersection_pt = view_ray.get_orig() + t * view_ray.get_dir();
    Color pix_col = hit_obj->get_color() * ambient_intensity;
    if(!is_shadow(intersection_pt)){
        //pix_col = pix_col + ...
    }
}

bool ofApp::is_shadow(const Point &intersection_pt){
    bool is_shadow = false;
    double epsilon = 0.001;
    Shape *shadow_obj;
    vector<Vec3d> light_directions;
    for(int i = 0; i < lights.size(); i++){
        light_directions.push_back(lights[i] - intersection_pt);
    }
    // generate rays for each light source
    for(int i = 0; i < light_directions.size(); i++){ 
        Point sh_ray_origin = intersection_pt + light_directions[i].normalize() * epsilon;
        Ray shadow_ray{sh_ray_origin, light_directions[i]};
        is_shadow = check_intersection(shadow_ray, shadow_obj, 0.0, numeric_limits<double>::infinity);
    }
    return is_shadow;
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
