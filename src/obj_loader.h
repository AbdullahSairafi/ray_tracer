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
        // get the prefix
        ss.str(""); // empty buffer
        ss.clear(); // reset error flags
        ss.str(line);
        ss >> prefix;
        if(prefix == "v"){ // vertex
            cout << "inside v case" << endl;
            double x, y, z;
            ss >> x >> y >> z;
            cout << x << " " << y << " " << z << endl;
            positions_v.push_back(Vec3d(x, y, z));
            // cout << "pushed vertex succesfully" << endl;
        }
        else if(prefix == "vt"){ // texture coordinate
            cout << "inside vt case" << endl;
            double x, y;
            ss >> x >> y;
            cout << x << " " << y << " " << endl;
            Vec2d temp;
            temp.x = x;
            temp.y = y;
            texcoords_v.push_back(temp);
            cout << "pushed vt successfully" << endl;
        }
        else if(prefix == "vn"){ // vertex normal
            double x, y, z;
            ss >> x >> y >> z;
            normals_v.push_back(Vec3d(x, y, z));
            cout << "pushed vn successfully" << endl;
        }
        else if(prefix == "f"){
            cout << "inside f case" << endl;
            int counter = 0;
            int temp;

            // vectors to store file info indices
            vector<int> verts_indices;
            vector<int> texcoords_indices;
            vector<int> normals_indices;

            // read the verices indcies
			while (ss >> temp)
			{
				//Pushing indices into correct arrays
				if (counter == 0)
					verts_indices.push_back(temp);
				else if (counter == 1)
					texcoords_indices.push_back(temp);
				else if (counter == 2)
					normals_indices.push_back(temp);

				//Handling characters
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				//Reset the counter
				if (counter > 2)
					counter = 0;
			}
            
            cout << "successfully read verices indices" << endl;
            for (int i = 0; i < verts_indices.size(); i++){
                cout << verts_indices[i] << " ";
            }
            cout << endl;
            // triangulate the face and push indices into faces vector
            int num_face_tris = verts_indices.size() - 2; // num verts per face - 2;
            for(int i = 0; i < num_face_tris; i++){
                Vec3i pos_inds;
                pos_inds.v[0] = verts_indices[0] - 1; // note -1 is because the vertices start from 1 instead of 0
                pos_inds.v[1] = verts_indices[i+1] - 1;
                pos_inds.v[2] = verts_indices[i+2] - 1;
                indices.positions_v.push_back(pos_inds);

                Vec3i nor_inds;
                nor_inds.v[0] = normals_indices[0] - 1;
                nor_inds.v[1] = normals_indices[i+1] - 1;
                nor_inds.v[2] = normals_indices[i+2] - 1;
                indices.normals_v.push_back(nor_inds);

                Vec3i tex_inds;
                tex_inds.v[0] = texcoords_indices[0] - 1;
                tex_inds.v[1] = texcoords_indices[i+1] - 1;
                tex_inds.v[2] = texcoords_indices[i+2] - 1;
                indices.texcoords_v.push_back(tex_inds);

            }

            // // build vertices:
            // for(size_t i = 0; i < verts_indices.size(); i++){
            //     Vertex temp_vertex;
            //     // note -1 is because the vertices start from 1 instead of 0
            //     temp_vertex.position = verts_positions[verts_indices[i]-1]; 
            //     temp_vertex.normal = verts_normals[normals_indices[i]-1];
            //     // temp_vertex.tex_coord = tex_coords[texcoords_indices[i]-1];
            //     vertices.push_back(temp_vertex);
            // }
            
            // cout << "vertices built" << endl;
        }
        else{ // do nothing for now

        }
    }

}

#endif