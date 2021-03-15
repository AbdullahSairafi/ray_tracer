#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <vector>
#include "vector.h"
#include "shapes.h"
#include "ray.h"
#include "camera.h"
using namespace std;

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	
	void add_shapes();
	void add_lights();
	bool check_intersection(Ray view_ray, Shape *&hit_obj, double t_low, double &t_up, int &t_idx);
	Color shading_model(Ray view_ray, Shape *hit_obj, double t);
	bool is_shadow(const Point &light_src, const Point &intersection_pt);
	Color diffuse_color(const Point &light, const Point &intersection_pt, Shape *hit_obj);
	Color specular_color(const Point &light, const Point &intersection_pt, Shape *hit_obj);
	void ray_tracer();
private:
	int w = 2048;
	int h = 1536;
	ofPixels colorPixels;
	ofTexture texColor;
	vector<Shape*> pShapes;
	vector<Point> lights;
	double ambient_intensity = 0.6;
	double light_intensity = 1.0;
	PrespectiveCamera *cam;
	double l = -2.0;
	double r = 2.0;
	double bm = -1.5;
	double tp = 1.5;
	int tri_idx;
};

