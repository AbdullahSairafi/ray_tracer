#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

//STD Libs
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cassert>
// own libs
#include "vector.h"
#include "shapes.h"

void load_obj_file(string &filename, vector<Vec3d> &positions_v,
                   vector<Vec3d> &normals_v, vector<Vec2d> &texcoords_v, Face_Indices &indices){
    // open file
    ifstream in_file(filename);
    // error handling
    if(!in_file){
        cerr << "Error: could not open " << filename << endl;
        exit(-1);
    }

    // read file 

    stringstream ss;
    string line;
    string prefix;
    
    while(getline(in_file, line)){
        // clear the stringstream and prefix string
        ss.str(""); // empty buffer
        ss.clear(); // reset error flags
        prefix = ""; // reset prefix\

        // read prefix
        ss.str(line);
        ss >> prefix;
        
        if(prefix == "v"){ // vertex
            double x, y, z;
            ss >> x >> y >> z;
            positions_v.push_back(Vec3d(x, y, z));
        }
        else if(prefix == "vt"){ // texture coordinate
            double x, y;
            ss >> x >> y;
            Vec2d temp;
            temp.x = x;
            temp.y = y;
            texcoords_v.push_back(temp);
        }
        else if(prefix == "vn"){ // vertex normal
            double x, y, z;
            ss >> x >> y >> z;
            normals_v.push_back(Vec3d(x, y, z));
        }
        else if(prefix == "f"){
            string element; // element is v/[vt]/[vn], vt, vn are optional  

            // vectors to store file info indices
            vector<int> verts_indices;
            vector<int> texcoords_indices;
            vector<int> normals_indices;

            // read the verices indcies
			while (ss >> element){
                int counter = 0;
                stringstream element_ss;
                element_ss.str(element);
                int val;
                while (element_ss >> val){
                    //Pushing indices into correct arrays
                    if (counter == 0)
                        verts_indices.push_back(val);
                    else if (counter == 1)
                        texcoords_indices.push_back(val);
                    else if (counter == 2)
                        normals_indices.push_back(val);

                    //Handling characters
                    if (ss.peek() == '/')
                    {
                        counter++;
                        ss.ignore(1, '/');
                        if(ss.peek() == '/'){
                            counter++;
                            ss.ignore(1, '/');
                        }
                    }
                    else if (ss.peek() == ' ')
                    {
                        counter++;
                        ss.ignore(1, ' ');
                    }

                    //Reset the counter
                    if (counter > 2){
                        counter = 0;
                    }
					
                }
                
				
			}
            
            // triangulate the face and push indices into faces vector
            int num_face_tris = verts_indices.size() - 2; // num verts per face - 2;
            for(int i = 0; i < num_face_tris; i++){
                Vec3i pos_inds;
                pos_inds.v[0] = verts_indices[0] - 1; // note -1 is because the vertices start from 1 instead of 0
                pos_inds.v[1] = verts_indices[i+1] - 1;
                pos_inds.v[2] = verts_indices[i+2] - 1;
                indices.positions_v.push_back(pos_inds);
                
                if(normals_indices.size() >= 3){
                    Vec3i nor_inds;
                    nor_inds.v[0] = normals_indices[0] - 1;
                    nor_inds.v[1] = normals_indices[i+1] - 1;
                    nor_inds.v[2] = normals_indices[i+2] - 1;
                    indices.normals_v.push_back(nor_inds);
                }
               
                if(texcoords_indices.size() >= 3){
                    Vec3i tex_inds;
                    tex_inds.v[0] = texcoords_indices[0] - 1;
                    tex_inds.v[1] = texcoords_indices[i+1] - 1;
                    tex_inds.v[2] = texcoords_indices[i+2] - 1;
                    indices.texcoords_v.push_back(tex_inds);
                }
                
            }

        }
        else{ 
            // do nothing for now
        }
    }

}

#endif