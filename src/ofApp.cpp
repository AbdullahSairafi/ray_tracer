#include "ofApp.h"
#include <limits>
#include <algorithm> 
#include <cmath>
#include <cassert>

#include "obj_loader.h"
//--------------------------------------------------------------
void ofApp::setup(){
    add_shapes();
    add_lights();
    cam = new PrespectiveCamera{Point{0.0, 0.0, 6.0}, Point{}, Vec3d{0.0, 1.0, 0.0}};
    cam->print_info();
    colorPixels.allocate(w, h, OF_PIXELS_RGB);
   
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // ofSetHexColor(0xffffff);
    // colorPixels.allocate(w, h, OF_PIXELS_RGB);
    ray_tracer();
    texColor.allocate(colorPixels);
	texColor.draw(0, 0);
}

void ofApp::add_shapes(){
    // Triangle *tr{new Triangle(Vec3d(0.0, 0.0, 0.0), Vec3d(1.5, 0.0, 0.0), Vec3d(0.0, 1.5, 0.0), Color(0, 100, 130))};
   
    // load the obj file
    string filename = "/home/as/Desktop/projects/cpp/ray_tracer/src/cube.obj";
    load_obj_file(filename, positions_v, normals_v, texcoords_v, indices);
    Mesh mesh(&positions_v, &normals_v, &texcoords_v, &indices);
    Mesh *cube = new Mesh(&positions_v, &normals_v, &texcoords_v, &indices);
    pShapes.push_back(cube);
    cout << "number of objects = " << pShapes.size() << endl;
    if(pShapes[0]->get_type() == ShapeType::MESH){
        cout << "type = mesh" << endl;
    }
}

void ofApp::add_lights(){
    lights.push_back(Point{1.0, 1.0, 1.0});
    // lights.push_back(Point{3.0, 3.0, -1.0});
}

bool ofApp::check_intersection(Ray view_ray, Shape *&hit_obj, double t_low, double &t_up, int &t_idx){
    bool hit = false;
    double t = std::numeric_limits<double>::min(); // initilize to -inf
    for(size_t i = 0; i < pShapes.size(); i++){
        if(pShapes[i]->get_type() == ShapeType::MESH){ // call the intersect function for mesh type
            if(pShapes[i]->intersect(view_ray, t, t_low, t_up, t_idx)){
                hit = true;
                t_up = t;
                hit_obj = pShapes[i]; // update hit object
            }
            // cout << "inside check_intersection, type=Mesh" << endl;
        }
        else{
            if(pShapes[i]->intersect(view_ray, t, t_low, t_up)){
                hit = true;
                t_up = t;
                hit_obj = pShapes[i]; // update hit object
            }
        }
        
    }
    if(hit_obj == nullptr){ // enforce a valid object in hit_obj pointer.
        return false;
    }
    return hit;
}

Color ofApp::shading_model(Ray view_ray, Shape *hit_obj, double t){
    assert(hit_obj);
    Point intersection_pt = view_ray.get_orig() + t * view_ray.get_dir();
    Color pix_col = hit_obj->get_color() * ambient_intensity;
    for(size_t i = 0; i < lights.size(); i++){
        if(!is_shadow(lights[i],  intersection_pt)){
            pix_col = pix_col + diffuse_color(lights[i], intersection_pt, hit_obj) + specular_color(lights[i], intersection_pt, hit_obj);
        }
    }
    
    return pix_col;
}

bool ofApp::is_shadow(const Point &light_src, const Point &intersection_pt){
    bool is_shadow = false;
    double epsilon = 0.001;
    Shape *shadow_obj = nullptr;
    Vec3d light_dir = (light_src - intersection_pt).normalize();
    // generate shadow ray for light source
    Point sh_ray_origin = intersection_pt + light_dir * epsilon; // add offset to avoid self-intersection
    Ray shadow_ray{sh_ray_origin, light_dir};
    double t_up = std::numeric_limits<double>::max();
    int temp_idx;
    is_shadow = check_intersection(shadow_ray, shadow_obj, 0.0, t_up, temp_idx);
    return is_shadow;
}

Color ofApp::diffuse_color(const Point &light, const Point &intersection_pt, Shape *hit_obj){
    Vec3d light_dir = (light - intersection_pt).normalize();
    Vec3d normal;
    if(hit_obj->get_type() == ShapeType::MESH){
        normal = hit_obj->normal(tri_idx);
    }
    else{
        normal = hit_obj->normal(intersection_pt);
    }
    Color diff_col = hit_obj->get_color() * light_intensity * std::max(0.0, dot(normal, light_dir));
    return diff_col;
}

Color ofApp::specular_color(const Point &light, const Point &intersection_pt, Shape *hit_obj){
    // for info look up this wiki link
    Vec3d light_dir = (light - intersection_pt).normalize();
    Vec3d v = (cam->get_orig() - intersection_pt).normalize();
    Vec3d h = (light_dir + v).normalize();
    Vec3d normal;
    if(hit_obj->get_type() == ShapeType::MESH){
        normal = hit_obj->normal(tri_idx);
    }
    else{
        normal = hit_obj->normal(intersection_pt);
    }
    Color spec_col = Color(128, 128, 128) * light_intensity * std::pow(std::max(0.0, dot(normal, h)), 100);
    return spec_col;
}

void ofApp::ray_tracer(){
    
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            // start from top left corner of the screen.
            double u = l + ((r - l) * (i + 0.5)) / (double)w;
            double v = tp - ((tp - bm) * (j + 0.5)) / (double)h;

            Ray ray{cam->make_ray(u, v)};
            Shape *hit_obj = nullptr;
            double t = std::numeric_limits<double>::max();
            int tri_idx = -1;
            if(check_intersection(ray, hit_obj, 0.0, t, tri_idx)){ 
                // cout << "found intersection" << endl;
                Color col = shading_model(ray, hit_obj, t);
                // cout << "rbg = " << col.get_r() << " " << col.get_g() << " " << col.get_b() << endl;
                colorPixels.setColor(i, j, ofColor(col.get_r(), col.get_g(), col.get_b()));
            }
            else{ // backgroud color (black)
                colorPixels.setColor(i, j, ofColor(0, 0, 0));
            }
        }
    }
    
    // colorPixels.setColor(x, y, ofColor(pix_col.r, pix_col.g, pix_col.b))
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    // camera movements:
    switch (key)
    {
    case 'w':
        cam->move_camera('u');
        break;
    case 'a':
        cam->move_camera('l');
        break;
    case 's':
        cam->move_camera('d');
        break;
    case 'd':
        cam->move_camera('r');
        break;
    case 'f':
        cam->move_camera('f');
        break;
    case 'b':
        cam->move_camera('b');
        break;
    case 'j': // left arrow
        // cout << "left arrow clicked" << endl;
        cam->move_target('l');
        break;
    case 'i': // up arrow
        cam->move_target('u');
        break;
    case 'l': // right arrow
        cam->move_target('r');
        break;
    case 'k': // down arrown
        cam->move_target('d');
        break;
    
    default:
        break;
    }
    // when exsiting, free allocated resources.
    if(key == 27){
        cout << "good bye" << endl;
        for(size_t i = 0; i < pShapes.size(); i++){
            delete pShapes[i];
        }
        // free cam pointer
        delete cam;
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
